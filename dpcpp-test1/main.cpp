#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <CL/sycl.hpp>
#include "a.h"
using namespace cl::sycl;

class SoftmaxForwardKernelName {};

void sycl_SoftMaxForward(buffer<float, 1> &output, buffer<float, 1> &input, int classes, int out_size)
{
  static const auto write_mode = cl::sycl::access::mode::discard_write;
  static const auto read_mode = cl::sycl::access::mode::read;
  using local_accessor_t = cl::sycl::accessor<float, 1, cl::sycl::access::mode::read_write, cl::sycl::access::target::local>;
  queue sycl_queue;
  int64_t local_size = sycl_queue.get_device(). template get_info<cl::sycl::info::device::max_work_group_size>();
  int64_t global_size = out_size * local_size;
  sycl_queue.submit([&](cl::sycl::handler &cgh) {
    auto in_acc = input.get_access<access::mode::read>(cgh);
    auto out_acc = output.get_access<access::mode::write>(cgh);
    auto local_acc_max = local_accessor_t(classes, cgh);
    auto local_acc_sum = local_accessor_t(classes, cgh);
    cgh.parallel_for<SoftmaxForwardKernelName> (
      cl::sycl::nd_range<1>(cl::sycl::range<1>(global_size), cl::sycl::range<1>(local_size)),
      [=](cl::sycl::nd_item<1> item_id){
        auto local_id = item_id.get_local_id(0);
        auto group_id = item_id.get_group(0);
        auto in_ptr = in_acc.template get_pointer<float>() + classes * group_id;
        auto out_ptr = out_acc.template get_pointer<float>()  + classes * group_id;
        // get max 
        local_acc_max[local_id] = in_ptr[0];
        for (int i = local_id; i < classes; i += local_size) {
          local_acc_max[local_id] = cl::sycl::max(local_acc_max[local_id], in_ptr[i]);
        }
        for(int i = (local_size >> 1); i > 0; i >>= 1) {
          item_id.barrier(cl::sycl::access::fence_space::local_space);
          if (local_id < i )  
            local_acc_max[local_id] = cl::sycl::max(local_acc_max[local_id], local_acc_max[local_id + i]);
        }

        // get sum
        local_acc_sum[local_id] = static_cast<float>(0);
        for (int i = local_id; i < classes; i += local_size) {
          local_acc_sum[local_id] += cl::sycl::exp(in_ptr[i] - local_acc_max[0]);
        }

        for(int i = (local_size >> 1); i > 0; i >>= 1) {
          item_id.barrier(cl::sycl::access::fence_space::local_space);
          if (local_id < i)  
            local_acc_sum[local_id] += local_acc_sum[local_id + i];
        }
        item_id.barrier(cl::sycl::access::fence_space::local_space);
      }); 
  });
}

int main() {
  int a = std::isinf(3.0);
  int b = std::isnan(0.0);
  std::string s = std::to_string(1);
  buffer<float, 1> input(range<1>{100});
  buffer<float, 1> output(range<1>{100});
  sycl_SoftMaxForward(output, input, 1, 1);
  foo();
  return 0;
}

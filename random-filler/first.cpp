#include <CL/sycl.hpp>
#include <limits>
#include <numeric>
#include "a.hpp"

using namespace cl::sycl;

void kernel1(queue Queue) {
  Queue.submit([&](cl::sycl::handler &cgh){
    FloatRandomFiller uniform_rnd_filler;
    auto num_work_items = cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256));
    cgh.parallel_for(num_work_items, uniform_rnd_filler);
  });
}

void kernel2(queue Queue) {
  Queue.submit([&](cl::sycl::handler &cgh){
    FloatRandomFiller uniform_rnd_filler;
    auto num_work_items = cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256));
    cgh.parallel_for(num_work_items, uniform_rnd_filler);
  });
}

cl::sycl::device getGPUDevice() {
  auto plaform_list = cl::sycl::platform::get_platforms();
  for(const auto& platform : plaform_list){
    auto device_list = platform.get_devices();
    for(const auto& device : device_list){
      if (device.is_gpu()) {
        std::cout << device.get_info<cl::sycl::info::device::name>() << std::endl;
        return device;
      }
    }
  }
  exit(1);
}

int main() {
  queue Queue(getGPUDevice());

  kernel1(Queue);
  kernel2(Queue);
  kernel3(Queue);

  return 0;
}

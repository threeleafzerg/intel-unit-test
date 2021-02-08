#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <assert.h>
#include <utility>
#include <tuple>

using namespace std;

const uint64_t VAL1 = 10;
const float VAL2 = 10;

namespace DP = cl::sycl;
static constexpr auto dp_global_space = DP::access::address_space::global_space;
template <typename T, DP::access::address_space Space = dp_global_space>
using dp_multi_ptr = typename DP::multi_ptr<T, Space>;


static void handle_exception(const cl::sycl::exception &e) {
  std::cout << "SYCL exception caught: " << e.what() << std::endl;
}

static void handle_exceptions(const cl::sycl::exception_list &l) {
  std::cout << "SYCL exception handler called\n";

  for (cl::sycl::exception_ptr_class const& eptr : l) {
    try {
      std::rethrow_exception(eptr);
    }
    catch (cl::sycl::exception const& e) {
      std::cout << "Caught asynchronous SYCL exception: " << e.what() << std::endl;
    }
  }
}

//template<typename T> 
long long run_test_a(long long v, cl::sycl::queue &deviceQueue) {
    try {
      long long arr[] = {v};
      {
        cl::sycl::buffer<long long, 1> buf(arr, 1);
        std::tuple<int, int> my_tuple = std::make_tuple(2, 1);
        deviceQueue.submit([&](cl::sycl::handler &cgh) {
          auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
          cgh.single_task<class kernel_a>([=]() { 
            // foo_acc[0] *= cl::sycl::fabs(-2.0f);
            acc[0] *= std::get<0>(my_tuple);
          });
        });
        deviceQueue.wait_and_throw();
      }
      return arr[0];
    }
    catch (cl::sycl::exception &e) {
      handle_exception(e);
    }
    return v;
}

int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue(handle_exceptions);

  //uint64_t ret1 = run_test_a<uint64_t>(VAL1, deviceQueue);
  // cl::sycl::queue *my_queue = new  cl::sycl::queue();
  long long ret2 = run_test_a(20, deviceQueue);
  std::cout << "ret2 = " << ret2 << std::endl;
  return 0;
}

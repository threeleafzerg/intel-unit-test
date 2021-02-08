#include <CL/sycl.hpp>

class kernel_b {};

int run_test_b(int v) {
  int arr[] = {v};
  {
    cl::sycl::queue deviceQueue;
    cl::sycl::buffer<int, 1> buf(arr, 1);
    deviceQueue.submit([&](cl::sycl::handler &cgh) {
      auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
      cgh.single_task<kernel_b>([=]() { acc[0] *= 3; });
    });
  }
  return arr[0];
}

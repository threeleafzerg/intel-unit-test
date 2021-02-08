#include <CL/sycl.hpp>
#include <iostream>

using namespace std;

const int VAL = 10;

extern int run_test_b(int);

class kernel_a {};

int run_test_a(int v) {
  int arr[] = {v};
  {
    cl::sycl::queue deviceQueue;
    cl::sycl::buffer<int, 1> buf(arr, 1);
    deviceQueue.submit([&](cl::sycl::handler &cgh) {
      auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
      cgh.single_task<kernel_a>([=]() { acc[0] *= 2; });
    });
  }
  return arr[0];
}

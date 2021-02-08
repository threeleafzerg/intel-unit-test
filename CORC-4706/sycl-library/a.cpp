#include <iostream>
#include "a.h"

int run_test_a(int v, cl::sycl::queue &deviceQueue) {
    int arr[] = {v};
    {
      cl::sycl::buffer<int, 1> buf(arr, 1);
      deviceQueue.submit([&](cl::sycl::handler &cgh) {
        auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
        cgh.single_task<class kernel_a>([=]() { acc[0] *= 2; });
      });
      deviceQueue.wait_and_throw();
    }
    return arr[0];
}


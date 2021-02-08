#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <cmath>

using namespace std;
using namespace cl::sycl;

int main(int argc, char **argv) {
  cl::sycl::queue queue;
  queue.submit([&](handler &cgh) { 
    cgh.parallel_for<class test>(cl::sycl::nd_range<1>(cl::sycl::range<1>(512), cl::sycl::range<1>(512)),
    [&](cl::sycl::nd_item<1> item_id) {
      auto gi = item_id.get_global_linear_id();
    }); 
  });
  return 0;
}

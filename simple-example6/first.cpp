#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <cmath>

using namespace std;

namespace hardware {

struct Device {
  int device_id;
};

int getDeviceID(Device dev) {
  return dev.device_id;
}

}

int main(int argc, char **argv) {
  cl::sycl::queue queue;
  queue.submit([&](cl::sycl::handler &cgh) { 
    char *a = (char *)malloc(1);
    cgh.parallel_for<class test>(cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256)),
    [&](cl::sycl::nd_item<1> item_id) {
      *a = 1;
    }); 
  });
  return 0;
}

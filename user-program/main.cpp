#include <iostream>
#include "a.h"
#include <CL/sycl.hpp>

int main(int argc, char **argv) {

  cl::sycl::queue deviceQueue;

  int i = 10;

  int ret = run_test_a(i, deviceQueue);

  std::cout << "ret:" << ret << std::endl;

  return ret;
}


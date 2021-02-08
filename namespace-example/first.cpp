#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <cmath>
#include "test_h/a.h"

using namespace std;
using namespace cl::sycl;

namespace test1 {
namespace {
 using namespace hello::world;
 void test(cl::sycl::buffer<int, 1>& buf, cl::sycl::queue& queue) {
   randomFill(buf, queue);
 } 
  
} 
}

int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue;
  int arr[256] = {0};
	cl::sycl::buffer<int, 1> buf(arr, 256);
	test1::test(buf, deviceQueue);
  deviceQueue.wait_and_throw();
	
	for (int i = 0; i < 256; i++) {
	  printf("arr[%d] = %d \n", i, arr[i]);
	}
  
  return 0;
}

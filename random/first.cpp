#include <iostream>
#include <random>
#include <stdlib.h>

#include "THSYCLTensorRandomKernel.hpp"

using namespace std;
using namespace cl::sycl;

const int VAL = 10;

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

void workFunction(buffer<uint8_t, 1>& buf, queue& myQueue, const range<1> r) { 
	myQueue.submit([&](handler& cgh) {
	auto ptr = buf.get_access<access::mode::read_write>(cgh); 
  auto num_work_items = cl::sycl::nd_range<1>(cl::sycl::range<1>(1), cl::sycl::range<1>(1));
#if 0
	FloatRandomFiller uniform_rand_filler(ptr, 1, 0x42, 0.0f, 1.0f); 
	cgh.parallel_for(num_work_items, uniform_rand_filler); 
#endif
#if 1
  cgh.parallel_for<class my_random>(num_work_items, 
    [=](cl::sycl::nd_item<1> item) {
	  FloatRandomFiller uniform_rand_filler(ptr, 1, 0x42, 0.0f, 1.0f); 
    uniform_rand_filler(item);
  });
	});
#endif
}


int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue(handle_exceptions);
  uint8_t arr = 0;
	try {
		cl::sycl::buffer<uint8_t, 1> buf(&arr, 1);
		auto it_range = range<1>(1);
		workFunction(buf, deviceQueue, it_range);
		deviceQueue.wait_and_throw();
	}
	catch (cl::sycl::exception &e) {
  	handle_exception(e);
  }
	
  return  0;
}

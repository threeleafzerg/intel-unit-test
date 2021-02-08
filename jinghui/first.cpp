#include <stdio.h>
#include <string.h>
#include <iostream>
#include <CL/sycl.hpp>

using namespace std;

class Dimension;

#ifdef __SYCL_DEVICE_ONLY__
  #define DPCPP_CONSTANT __attribute__((opencl_constant))
#else
  #define DPCPP_CONSTANT
#endif


#define DPCPP_KER_STRING(var, str) \
	static const DPCPP_CONSTANT char var[] = str;

int run_test_a(void) {
    cl::sycl::queue deviceQueue;
    deviceQueue.submit([&](cl::sycl::handler &cgh) {
			cgh.parallel_for<Dimension>( cl::sycl::nd_range<2>(cl::sycl::range<2>{3,4}, cl::sycl::range<2>{3,4}),
																	 [=](cl::sycl::nd_item<2> item_id) 
			{
				DPCPP_KER_STRING(format_str, "item_id[%d][%d] = %d\n");
				cl::sycl::intel::experimental::printf(format_str, item_id.get_local_id(0),
																													item_id.get_local_id(1),
																													item_id.get_global_linear_id());
			});
    });
    deviceQueue.wait_and_throw();
    return 0;
}

int main(int argc, char **argv) {
  int test_a = run_test_a();
  return 0;
}


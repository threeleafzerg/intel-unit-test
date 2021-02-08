#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <assert.h>
using namespace std;

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

struct A {
	int m;
};

struct B {
	B (const A &rhs): val(rhs) {};
	const A val;
};

long long run_test_a(long long v, cl::sycl::queue &deviceQueue) {
	int arr[] = {(int)v};
	{
	cl::sycl::buffer<int, 1> buf(arr, 1);
	A a;
	a.m = 42;
	B b(a);
  deviceQueue.submit([&](cl::sycl::handler &cgh) {
					auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
          cgh.parallel_for<class run_test>(cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256)),						
					  [=](cl::sycl::nd_item<1> item_id) {
							auto gid = item_id.get_global_linear_id();
							acc[0] = b.val.m;
          });
  });
	deviceQueue.wait_and_throw();
	}
  return arr[0];
}

int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue(handle_exceptions);

  long long ret2 = run_test_a(0, deviceQueue);
	std::cout << "ret2 = " << ret2 << std::endl;
  return 0;
}

#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <assert.h>
using namespace std;

const uint64_t VAL1 = 10;
const float VAL2 = 10;

//namespace DP = cl::sycl;
//static constexpr auto dp_global_space = DP::access::address_space::global_space;
//template <typename T, DP::access::address_space Space = dp_global_space>
//using dp_multi_ptr = typename DP::multi_ptr<T, Space>;


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

struct B {
public:
  virtual void foo() { return; }
  int i; 
};

long long run_test_a(long long v, cl::sycl::queue &deviceQueue) {
	int arr[] = {(int)v};
	{
	cl::sycl::buffer<int, 1> buf(arr, 1);
  B b;
  b.i = 1;
  deviceQueue.submit([&](cl::sycl::handler &cgh) {
		auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
      cgh.parallel_for<class run_test>(cl::sycl::nd_range<1>(cl::sycl::range<1>(256*256*256 +256), cl::sycl::range<1>(256)),						      [=](cl::sycl::nd_item<1> item_id) {
							auto gid = item_id.get_global_linear_id();
							if (gid > 256 * 256 * 256) {
								acc[0] = acc[0] > gid ? acc[0] : gid;
                acc[0] += b.i;
							}
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

#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <assert.h>
using namespace std;

const uint64_t VAL1 = 10;
const float VAL2 = 10;

namespace DP = cl::sycl;
static constexpr auto dp_global_space = DP::access::address_space::global_space;
template <typename T, DP::access::address_space Space = dp_global_space>
using dp_multi_ptr = typename DP::multi_ptr<T, Space>;


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

typedef struct S {
	unsigned short x;
};

S foo(bool cond, const S &lhs, S rhs) {
	S val = cond ? lhs : rhs;
	return val;
}

//template<typename T> 
long long run_test_a(long long v, cl::sycl::queue &deviceQueue) {
  deviceQueue.submit([&](cl::sycl::handler &cgh) {
          cgh.single_task<class kernel_a>([=]() { 
						S lhs, rhs;
						auto ret = foo(true, lhs, rhs);
          });
  });
	deviceQueue.wait_and_throw();
  return 0;
}

int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue(handle_exceptions);

  //uint64_t ret1 = run_test_a<uint64_t>(VAL1, deviceQueue);
  long long ret2 = run_test_a(20, deviceQueue);
  return 0;
}

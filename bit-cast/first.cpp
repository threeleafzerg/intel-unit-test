#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>

using namespace std;

const int VAL = 10;


// TODO: move this to public cl::sycl::bit_cast as extension?
template <typename To, typename From> To bit_cast(const From &from) {
#if __cpp_lib_bit_cast
  return std::bit_cast<To>(from); 
#else

#if __has_builtin(__builtin_bit_cast)
  return __builtin_bit_cast(To, from);  // clang path
#else
  To to;
  detail::memcpy(&to, &from, sizeof(To));
  return to;
#endif // __has_builtin(__builtin_bit_cast)
#endif // __cpp_lib_bit_cast
}


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

int run_test_a(int v, cl::sycl::queue &deviceQueue) {
    try {
      int arr[] = {v};
			unsigned short arr1[] = {0};
      {
        cl::sycl::buffer<int, 1> buf(arr, 1);
				cl::sycl::buffer<unsigned short, 1> buf1(arr1, 1); 
        deviceQueue.submit([&](cl::sycl::handler &cgh) {
          auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
          auto acc1 = buf1.get_access<cl::sycl::access::mode::read_write>(cgh);
          cgh.single_task<class kernel_a>([=]() { 
						acc[0] *= 2;  
						cl::sycl::half a(1.0f);
						acc1[0] = bit_cast<unsigned short, cl::sycl::half>(a);
					});
        });
        deviceQueue.wait_and_throw();
      }
			std::cout << "arr1[0]=" << arr1[0] << std::endl;
      return arr[0];
    }
    catch (cl::sycl::exception &e) {
      handle_exception(e);
    }
    return 0;
}

int main(int argc, char **argv) {
  bool pass = true;
  cl::sycl::queue deviceQueue(handle_exceptions);

  int test_a = run_test_a(VAL, deviceQueue);
  const int GOLD_A = 2*VAL;

  if (test_a != GOLD_A) {
    std::cout << "FAILD test_a. Expected: " << GOLD_A << ", got: " << test_a << "\n";
    pass = false;
  }

  if (pass) {
    std::cout << "pass\n";
  }
  return pass ? 0 : 1;
}

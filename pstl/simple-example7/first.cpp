#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <cmath>
#include <utility>

using namespace std;

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

int run_test_a(int v, cl::sycl::queue &deviceQueue) {
      int arr[] = {10};
      {
        cl::sycl::buffer<int, 1> buf(arr, 1);
        deviceQueue.submit([&](cl::sycl::handler &cgh) {
          cl::sycl::stream stream(1024, 80, cgh);
          auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
          cgh.single_task<class kernel_a>([=]() {
            long x = acc[0];
            float y = acc[0];
            acc[0] *= 3; 
          });
        });
        deviceQueue.wait_and_throw();
      }
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
  const int GOLD_A = 3*VAL;

  if (test_a != GOLD_A) {
    std::cout << "FAILD test_a. Expected: " << GOLD_A << ", got: " << test_a << "\n";
    pass = false;
  }

  if (pass) {
    std::cout << "pass\n";
  }
  return pass ? 0 : 1;
}

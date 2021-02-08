#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
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

#define N     5
#if 1
struct MyArray {
public:
  int arr1[N][N];
  int arr2[N][N];
  int arr3[N][N];
  int arr4[N][N];
  int arr5[N][N];
private:
  int a;
public:
  int func() const { return a;}
};
#endif

#if 0
struct MyArray {
  int arr1[N * N];
  int arr2[N * N];
  int arr3[N * N];
  int arr4[N * N];
  int arr5[N * N];
};
#endif

int run_test_a(long long v, cl::sycl::queue &deviceQueue) {
    try {
      MyArray arr_list;
      //std::cout << "sizeof MyArray Host:" << sizeof(MyArray);
      std::fill((int *)arr_list.arr1, (int *)(arr_list.arr1) + N*N, 1); 
      std::fill((int *)arr_list.arr2, (int *)(arr_list.arr2) + N*N, 1); 
      std::fill((int *)arr_list.arr3, (int *)(arr_list.arr3) + N*N, 1); 
      std::fill((int *)arr_list.arr4, (int *)(arr_list.arr4) + N*N, 1); 
      std::fill((int *)arr_list.arr5, (int *)(arr_list.arr5) + N*N, 1); 
      //std::fill((int *)arr_list.a, (int *)(arr_list.a) + 10, 0); 
      int scalar[] = {0}; 
      {
        cl::sycl::buffer<int , 1> buf(scalar, 1);
        deviceQueue.submit([&](cl::sycl::handler &cgh) {
          auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
          cgh.parallel_for<class kernel_a>(cl::sycl::range<1>(1), [=](cl::sycl::item<1> id) {
            // printf("sizeof MyArray Device: %d\n", sizeof(MyArray));
            //auto b = arr_list.func();
            for (int i = 0; i < N; i++) 
              for (int j = 0; j < N; j++) {
#if 1
                acc[0] += arr_list.arr1[i][j];
                acc[0] += arr_list.arr2[i][j];
                acc[0] += arr_list.arr3[i][j];
                acc[0] += arr_list.arr4[i][j];
                acc[0] += arr_list.arr5[i][j];
#endif

#if 0
                acc[0] += arr_list.arr1[i*N + j];
                acc[0] += arr_list.arr2[i*N + j];
                acc[0] += arr_list.arr3[i*N + j];
                acc[0] += arr_list.arr4[i*N + j];
                acc[0] += arr_list.arr5[i*N + j];
#endif
              }
          });
        });
        deviceQueue.wait_and_throw();
      }
      return scalar[0];
    }
    catch (cl::sycl::exception &e) {
      handle_exception(e);
    }
    return v;
}



int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue(handle_exceptions);

  //uint64_t ret1 = run_test_a<uint64_t>(VAL1, deviceQueue);
  long long ret2 = run_test_a(20, deviceQueue);
  std::cout << "ret2 = " << ret2 << std::endl;
  return 0;
}

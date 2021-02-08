#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;

// printf utils
#ifdef __SYCL_DEVICE_ONLY__
  #define DPCPP_CONSTANT __attribute__((opencl_constant))
#else
  #define DPCPP_CONSTANT
#endif

#define DPCPP_KER_STRING(var, str) \
  static const DPCPP_CONSTANT char var[] = str;

#ifdef __SYCL_DEVICE_ONLY__
  #define DPCPP_PRINTF cl::sycl::ONEAPI::experimental::printf
#else
  #define DPCPP_PRINTF printf
#endif

#define MAGIC_NUM 42

void runKernel1(int *devPtr, cl::sycl::queue &q) {
  auto event = q.submit([&](handler &cgh) {
    cgh.single_task<class runKernel1>([=]() {
      DPCPP_KER_STRING(format_str1, "Dev Ptr=%p\n");
      DPCPP_KER_STRING(format_str2, "Ref Ptr=%d\n");
      DPCPP_PRINTF(format_str1, devPtr);
      *devPtr = MAGIC_NUM;
      DPCPP_PRINTF(format_str2, *devPtr);
    });
  });
  event.wait();
}

void runKernel2(int *devPtr, cl::sycl::queue &q) {
  auto event = q.submit([&](handler &cgh) {
    cgh.single_task<class runKernel2>([=]() {
      DPCPP_KER_STRING(format_str2, "Ref Ptr=%d\n");
      DPCPP_PRINTF(format_str2, *devPtr);
    });
  });
  event.wait();
}

int main() {
  int *pDev = nullptr;
  cl::sycl::device dev {cl::sycl::gpu_selector {}};
  cl::sycl::queue q1(dev);
  cl::sycl::queue q2(dev);
  cl::sycl::context ext_ctx({dev});

  pDev = (int *)malloc_device((size_t)3096*1024*1024, dev, ext_ctx);
  if (pDev == nullptr) {
    std::cout << "malloc_device failed!\n" << std::endl;
    return -1;
  } else {
    std::cout << "malloc_device succeed!\n" << std::endl;
  }

//  std::cout << "pDev=" << pDev << std::endl;
//  Normal Case
//  runKernel1(pDev, q1);
//  runKernel2(pDev, q2);
//  free(pDev, ext_ctx);
  std::cout << "Program Exit!" << std::endl;
  return 0;
}

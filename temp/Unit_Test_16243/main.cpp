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
  #define DPCPP_PRINTF cl::sycl::intel::experimental::printf
#else
  #define DPCPP_PRINTF printf
#endif

#define MAGIC_NUM 42

void runKernel(int *devPtr, cl::sycl::queue &q) {
  auto event = q.submit([&](handler &cgh) {
    cgh.single_task<class runKernel>([=]() {
      DPCPP_KER_STRING(format_str1, "Dev Ptr=%p\n");
      DPCPP_KER_STRING(format_str2, "Ref Ptr=%d\n");
      DPCPP_PRINTF(format_str1, devPtr);
      *devPtr = MAGIC_NUM;
      DPCPP_PRINTF(format_str2, *devPtr);
    });
  });
  event.wait();
}

int main() {
  int *pDev = nullptr;
  cl::sycl::device dev {cl::sycl::gpu_selector {}};
  cl::sycl::queue q(dev);
  auto ctxt = q.get_context();

  pDev = (int *)malloc_device(sizeof(int), dev, ctxt);
  if (pDev == nullptr) {
    std::cout << "malloc_device failed!\n" << std::endl;
    return -1;
  }

  //  Normal Case
  runKernel(pDev, q);
  //  NULL Pointer
  runKernel((int *)nullptr, q);
  //  Invalid Pointer
  runKernel((int *)0xdeadbeef, q);
  free(pDev, ctxt);
  std::cout << "Program Exit!" << std::endl;
  return 0;
}

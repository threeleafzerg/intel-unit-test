#include <CL/sycl.hpp>

using namespace cl::sycl;

#define USE_DPCPP 1

// printf utils
#if defined(USE_DPCPP)
  #ifdef __SYCL_DEVICE_ONLY__
    #define DPCPP_CONSTANT __attribute__((opencl_constant))
  #else
    #define DPCPP_CONSTANT
  #endif
#else
  #define DPCPP_CONSTANT
#endif

#define DPCPP_KER_STRING(var, str) \
  static const DPCPP_CONSTANT char var[] = str;

#if defined(USE_DPCPP)
  #define DPCPP_PRINTF cl::sycl::intel::experimental::printf
#else
  #define DPCPP_PRINTF printf
#endif

//const CONSTANT char format_int[] = "darray[0]=%d\n";
template<class T, int var> 
class Hello_World {};

int main() {
  int *darray = nullptr;
  const int MAGIC_NUM = 42;

  queue q;
  auto dev = q.get_device();
  auto ctxt = q.get_context();

  darray = (int *)malloc_device(sizeof(int), dev, ctxt);
  if (darray == nullptr) {
    return -1;
  }

  int const_var = 10;
  auto eInit = q.submit([&](handler &cgh) {
    cgh.single_task<Hello_World<float, const_var>>([=]() {
			DPCPP_KER_STRING(format_int, "darray[0]=%d\n");			
      darray[0] = MAGIC_NUM;
      for (int i = 0; i < 10; i++) {
        //intel::experimental::printf(format_int, darray[0]);
				DPCPP_PRINTF(format_int, darray[0]);
      }
      int i = cl::sycl::fabs((float)darray[0]);
    });
  });
  free(darray, ctxt);
  std::cout << "Program Exit!" << std::endl;
  eInit.wait();
  return 0;


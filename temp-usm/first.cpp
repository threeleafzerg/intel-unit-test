#include <CL/sycl.hpp>

using namespace cl::sycl;

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

// #define INT std::ptrdiff_t
//const CONSTANT char format_int[] = "darray[0]=%d\n";
//
class test {
public:
   //typedef int INT;
   using INT = const int;
};

template<typename T, T::INT var> 
// template<typename T, typename INT var> 
class Hello_World {
};

int main() {

  const int MAGIC_NUM = 42;

  queue q;

#if 1
  test::INT const_var = 10;
  auto eInit = q.submit([&](handler &cgh) {
    cgh.single_task<Hello_World<test, const_var>>([=]() {
    });
  });
#endif
  return 0;
}

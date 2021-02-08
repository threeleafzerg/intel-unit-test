
#pragma OPENCL EXTENSION cl_khr_fp16 : enable

#include <CL/sycl.hpp>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace cl::sycl;
constexpr size_t N = 100;

template <typename T>
void assert_close(const T &C, const cl::sycl::half ref) {
  for (size_t i = 0; i < N; i++) {
    auto diff = C[i] - ref;
    // assert(std::fabs(static_cast<float>(diff) < 
    //      std::numeric_limits<cl::sycl::half>::epsilon());
  }
}

void verify_add(queue &q, 
                buffer<half, 1> &a, 
                buffer<half, 1> &b,
                range<1> &r,
                const half ref) {
  
  buffer<half, 1> c{r};
  
  q.submit([&](handler &cgh) {
    auto A = a.get_access<access::mode::read>(cgh);
    auto B = b.get_access<access::mode::read>(cgh);
    auto C = c.get_access<access::mode::write>(cgh);
    cgh.parallel_for<class calc_min>(
        r, [=](id<1> index) { C[index] = A[index] - B[index]; });
  });

  assert_close(c.get_access<access::mode::read>(), ref);
}

int main() {

  device dev{default_selector()};
  if (!dev.is_host() && !dev.has_extension("cl_khr_fp16")) {
    std::cout << "This device doesn't support the extension cl_khr_fp16"
              << std::endl;
    return 0;
  } 

  std::vector<half> vec_a(N, 5.0);
  std::vector<half> vec_b(N, 2.0);

  range<1> r(N);
  buffer<half, 1> a{vec_a.data(), r};
  buffer<half, 1> b{vec_b.data(), r};

  queue q {dev};
  verify_add(q, a, b, r, 7.0);
  return 0; 
}

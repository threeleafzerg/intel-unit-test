#include <CL/sycl.hpp>
#include <chrono>
#include <iostream>


struct D1 {
  int i;
  int j;
  float a;
  double b;
};

struct D2 {
  char y;
  short z;
  float x[5];
};

class TEST_KER {};

int main() {
  int a = 5050;
  D1 d1 = {23, 68, 7.9535476, 56776345.878787};
  D2 d2 = {'v', 2329, {5.56,7.234,8.567,9.479,2.495}};

  cl::sycl::queue m_queue;

  int wgsize = 512;
  auto numInd = 16 * wgsize;

  auto cgf = [&](cl::sycl::handler &cgh) {
    cgh.parallel_for<TEST_KER>(
        cl::sycl::nd_range<1>(cl::sycl::range<1>(numInd), cl::sycl::range<1>(wgsize)),
        [=] (cl::sycl::nd_item<1> item) {
          auto index = item.get_global_linear_id();
          if (index > 10) {
            index ++;
          } else {
            index --;
          }
          index += a;
          if (d1.j >= 2 && d1.b < 0) {
            index += a;
          }
          index = d2.x[3];
          D1 x = d1;
          D2 y = d2;
          x.a = y.x[2];
        });
  };

  auto start = std::chrono::high_resolution_clock::now();
  m_queue.submit(cgf);
  auto first = std::chrono::high_resolution_clock::now() - start;

  start = std::chrono::high_resolution_clock::now();
  m_queue.submit(cgf);
  auto total = std::chrono::high_resolution_clock::now() - start;

  for (int i = 1; i < 100; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    m_queue.submit(cgf);
    total += std::chrono::high_resolution_clock::now() - start;
  }

  std::cout << " First("
    << std::chrono::duration_cast<std::chrono::microseconds>(first).count()
    << "us)" << " Avg("
    << (std::chrono::duration_cast<std::chrono::microseconds>(total).count() / 100)
    << "us)" << std::endl;
	m_queue.wait();
}

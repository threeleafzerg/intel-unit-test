#include <CL/sycl.hpp>
#include <stdlib.h>
#include <iostream>
#include <chrono> 
using namespace std::chrono;
using namespace cl::sycl;
using namespace std;
#define ELEMENT_NUM 10000000 * 16

void memcpyHostToDevice( 
  cl::sycl::buffer<float, 1> &buf, 
  const void *src,
  cl::sycl::queue &queue) {
  auto cgf = [&](cl::sycl::handler & cgh) {
    auto dst_acc = buf.template get_access<access::mode::read_write, access::target::global_buffer>(cgh);
    cgh.copy(src, dst_acc);
  };
  auto e = queue.submit(cgf);
  e.wait();
}

int main() {
  cl::sycl::device dev{cl::sycl::gpu_selector{}};
  cl::sycl::queue queue(dev);
  float *host_a = (float *)malloc(ELEMENT_NUM * sizeof(float));
  float *host_b = (float *)malloc(ELEMENT_NUM * sizeof(float));
  float *host_c = (float *)malloc(ELEMENT_NUM * sizeof(float));
  cl::sycl::buffer<float, 1> buf_a(range<1>(ELEMENT_NUM));
  cl::sycl::buffer<float, 1> buf_b(range<1>(ELEMENT_NUM));
  cl::sycl::buffer<float, 1> buf_c(range<1>(ELEMENT_NUM));

  // Copy host_a to acc_a
  auto start = std::chrono::steady_clock::now();
  memcpyHostToDevice(buf_a, host_a, queue);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> duration = end-start;
  std::cout << "Time taken by copy host_a to buf_a: "
       << duration.count() << " seconds" << std::endl;
  // Copy host_b to acc_b
  start = std::chrono::steady_clock::now();
  memcpyHostToDevice(buf_b, host_b, queue);
  end = std::chrono::steady_clock::now();
  duration = end - start;
  std::cout << "Time taken by copy host_b to buf_b: "
       << duration.count() << " seconds" << std::endl;
  // Copy host_c to acc_c
  start = std::chrono::steady_clock::now(); 
  memcpyHostToDevice(buf_c, host_c, queue);
  end = std::chrono::steady_clock::now();
  duration = end - start; 
  std::cout << "Time taken by copy host_c to buf_c: "
       << duration.count() << " seconds" << std::endl;
  return 0;
}

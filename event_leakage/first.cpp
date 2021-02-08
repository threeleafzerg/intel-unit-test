#include <CL/sycl.hpp>
#include <chrono>
#include <iostream>
#include <unistd.h>


class TEST_KER {};


void copy_func (void* src, int size, bool print = true) {
  cl::sycl::queue m_queue;
  auto dev = m_queue.get_device();
  auto ctx = m_queue.get_context();

  void* devPtr = cl::sycl::malloc_device(size, dev, ctx);

  int i = 5;
  do {
    auto e = m_queue.memcpy(devPtr, src, size);
    e.wait();
    i--;
  } while (i > 0);
  
  cl::sycl::free(devPtr, ctx);
}

void ker_func1() {
  cl::sycl::queue q{cl::sycl::gpu_selector{}};
  q.single_task<class test>([](){});
}

void ker_func2() {
  cl::sycl::queue q{cl::sycl::gpu_selector{}};
  auto e = q.single_task<class test2>([](){});
  e.wait();
}

int main() {
  for (int i = 0; i < 1000000; i++) {
    ker_func1();
    ker_func2();
    usleep(10000);
  }
  return 0;
}

#include <CL/sycl.hpp>
#include <chrono>
#include <iostream>


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


  auto start = std::chrono::high_resolution_clock::now();
  auto e = m_queue.memcpy(devPtr, src, size);
  e.wait();
  auto end = std::chrono::high_resolution_clock::now() - start;

  if (print) {
    std::cout << " size:" << size << " bytes ("
      << std::chrono::duration_cast<std::chrono::microseconds>(end).count()
      << "us)" << std::endl;
  }
}


int main() {
  char a = 'a';
  int size = sizeof(char);
  copy_func(&a, size, false);

  char a1 = 'a';
  size = sizeof(char);
  copy_func(&a1, size);

  int b = 10;
  size = sizeof(int);
  copy_func(&b, size);

  float c = 10.45454;
  size = sizeof(float);
  copy_func(&c, size);

  double d = 32343410.45454;
  size = sizeof(double);
  copy_func(&c, size);

  size = 1024;
  void* e = malloc(size);
  copy_func(e, size);

  size = 10240;
  void* k = malloc(size);
  copy_func(k, size);

  size = 102400;
  void* m = malloc(size);
  copy_func(m, size);

  size = 1024000;
  void* n = malloc(size);
  copy_func(n, size);

  size = 10240000;
  void* o = malloc(size);
  copy_func(o, size);

  size = 102400000;
  void* p = malloc(size);
  copy_func(p, size);

}

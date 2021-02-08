#include <CL/sycl.hpp>
#include <chrono>
#include <iostream>


class TEST_KER {};

int main() {
	int size = 616562688;

  cl::sycl::queue m_queue;
  auto dev = m_queue.get_device();
  auto ctx = m_queue.get_context();

  void* devPtr = cl::sycl::malloc_device(size, dev, ctx);

	for (int i = 0; i < 5; i++) {
    void* p = malloc(size);
    memset(p, 0x10, size);
		auto start = std::chrono::high_resolution_clock::now();
		auto e = m_queue.memcpy(devPtr, p, size);
		auto mid = std::chrono::high_resolution_clock::now();
		e.wait();
		auto end = std::chrono::high_resolution_clock::now();

		auto submit = mid - start;
		auto wait = end - mid;
		auto total = end - start;

		std::cout << " size:" << size << " bytes "
			<< "(submit: " << std::chrono::duration_cast<std::chrono::microseconds>(submit).count() << "us)"
			<< "(wait: " << std::chrono::duration_cast<std::chrono::microseconds>(wait).count() << "us)"
			<< "(total: " << std::chrono::duration_cast<std::chrono::microseconds>(total).count() << "us)"
			<< std::endl;

		free(p);
	}

  std::cout<< "----------with host cache-----------"<< std::endl;

	void* p = malloc(size);
	for (int i = 0; i < 5; i++) {
		auto start = std::chrono::high_resolution_clock::now();
		auto e = m_queue.memcpy(devPtr, p, size);
		auto mid = std::chrono::high_resolution_clock::now();
		e.wait();
		auto end = std::chrono::high_resolution_clock::now();
    //int *pi = (int *)p;
    //pi[4] = 3;
		auto submit = mid - start;
		auto wait = end - mid;
		auto total = end - start;

		std::cout << " size:" << size << " bytes "
			<< "(submit: " << std::chrono::duration_cast<std::chrono::microseconds>(submit).count() << "us)"
			<< "(wait: " << std::chrono::duration_cast<std::chrono::microseconds>(wait).count() << "us)"
			<< "(total: " << std::chrono::duration_cast<std::chrono::microseconds>(total).count() << "us)"
			<< std::endl;
	}
	free(p);
}

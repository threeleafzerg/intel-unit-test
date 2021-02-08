#include <stdio.h>
#include <string.h>
#include <iostream>
#include <CL/sycl.hpp>

using namespace std;
template<typename T>
using global_accessor_t =
    cl::sycl::accessor<T, 1, cl::sycl::access::mode::read_write, cl::sycl::access::target::global_buffer>;

template <typename T>
using local_accessor_t =
  cl::sycl::accessor<T, 1, cl::sycl::access::mode::read_write, cl::sycl::access::target::local>;

template<typename T>
struct RunOp {
public:
  RunOp(T i, void *p):m_i(i), m_p(p) {};
  void __attribute__((noinline)) run_a(const global_accessor_t<int> &acc, const local_accessor_t<int> &local_acc1, const local_accessor_t<int> &local_acc2, const local_accessor_t<int> &local_acc3, const local_accessor_t<int> &local_acc4, const cl::sycl::nd_item<2> &item_id) const {
    local_acc2[0] = 2;
    run_b(acc, local_acc1, local_acc2, local_acc3, local_acc4, item_id);
  };
  void __attribute__((noinline)) run_b(const global_accessor_t<int> &acc, const local_accessor_t<int> &local_acc1, const local_accessor_t<int> &local_acc2, const local_accessor_t<int> &local_acc3, const local_accessor_t<int> &local_acc4, const cl::sycl::nd_item<2> &item_id) const {
    local_acc3[0] = 3;
    run_c(acc, local_acc1, local_acc2, local_acc3, local_acc4, item_id);
  }
  void __attribute__((noinline)) run_c(const global_accessor_t<int> &acc, const local_accessor_t<int> &local_acc1, const local_accessor_t<int> &local_acc2, const local_accessor_t<int> &local_acc3, const local_accessor_t<int> &local_acc4, const cl::sycl::nd_item<2> &item_id) const {
    local_acc4[0] = 4;
    run_d(acc, local_acc1, local_acc2, local_acc3, local_acc4, item_id);
  }
  void __attribute__((noinline)) run_d(const global_accessor_t<int> &acc, const local_accessor_t<int> &local_acc1, const local_accessor_t<int> &local_acc2, const local_accessor_t<int> &local_acc3, const local_accessor_t<int> &local_acc4, const cl::sycl::nd_item<2> &item_id) const {
		local_acc1[0] = item_id.get_local_id(0);
    run_e(acc, local_acc1, local_acc2, local_acc3, local_acc4, item_id);
  }
  void __attribute__((noinline)) run_e(const global_accessor_t<int> &acc, const local_accessor_t<int> &local_acc1, const local_accessor_t<int> &local_acc2, const local_accessor_t<int> &local_acc3, const local_accessor_t<int> &local_acc4, const cl::sycl::nd_item<2> &item_id) const {
    acc[0] = acc[0] * 2 * local_acc1[0] * local_acc2[0] * local_acc3[0] * local_acc4[0] * m_i * m_a[99];
  }
public:
  T m_i;
  void *m_p;
  int m_a[1000];
};

template<typename RunType>
int run_test_a(const RunType runop) {
    cl::sycl::queue deviceQueue;
    int arr[] = {2};
    deviceQueue.submit([&](cl::sycl::handler &cgh) {
    cl::sycl::buffer<int, 1> buf(arr, 1);
    auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
		auto local_acc1 = local_accessor_t<int>(256, cgh);
		auto local_acc2 = local_accessor_t<int>(256, cgh);
		auto local_acc3 = local_accessor_t<int>(256, cgh);
		auto local_acc4 = local_accessor_t<int>(256, cgh);
    cgh.parallel_for<RunType>( cl::sycl::nd_range<2>(cl::sycl::range<2>{256,1}, cl::sycl::range<2>{256,1}),
                               [=](cl::sycl::nd_item<2> item_id) { runop.run_a(acc, local_acc1, local_acc2, local_acc3, local_acc4, item_id); });
    });
    deviceQueue.wait_and_throw();
    return arr[0];
}

int main(int argc, char **argv) {
  void *p = NULL;
  RunOp<int> runop(10, p);
  memset(runop.m_a, 100, sizeof(runop.m_a));
  int test_a = run_test_a(runop);
  printf("test_a = %d\n", test_a);
  return 0;
}


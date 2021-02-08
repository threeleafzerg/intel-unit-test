#include <CL/sycl.hpp>  
#include <iostream>  
#include <algorithm>
#include <chrono>

#include <stdlib.h>

using namespace cl::sycl;  

#define N 10

constexpr auto r_mode = cl::sycl::access::mode::read;
constexpr auto w_mode = cl::sycl::access::mode::write;

template <typename op_t>
void binary_func(cl::sycl::buffer<int, 1>out_buf,  cl::sycl::buffer<int, 1> in1_buf,  cl::sycl::buffer<int, 1> in2_buf, int len, op_t op) {
  queue gQueue;
  gQueue.submit([&](cl::sycl::handler &cgh) {
    auto in1 = in1_buf.get_access<r_mode>(cgh);
    auto in2 = in2_buf.get_access<r_mode>(cgh);
    auto out = out_buf.get_access<w_mode>(cgh);
    cgh.parallel_for<class binary_op>(cl::sycl::range<1>(len),
                                        [=](cl::sycl::id<1> i) {
                                        assert(0);
																				out[i] = op(in1[i], in2[i]);
                                        });
  });
}


void binary_func2(cl::sycl::buffer<int, 1>out_buf,  cl::sycl::buffer<int, 1> in1_buf,  cl::sycl::buffer<int, 1> in2_buf, int len) {
  queue gQueue;
  gQueue.submit([&](cl::sycl::handler &cgh) {
    auto in1 = in1_buf.get_access<r_mode>(cgh);
    auto in2 = in2_buf.get_access<r_mode>(cgh);
    auto out = out_buf.get_access<w_mode>(cgh);
    cgh.parallel_for<class binary_op2>(cl::sycl::range<1>(len),
                                        [=](cl::sycl::id<1> i) {
                                        assert(0);
																				out[i] = (in1[i] + in2[i]);
                                        });
  });
}

int main(int argc, char **argv) { 

  int in1[N] = {1,3,7,13,2,9,2,1,-10,-8};
  int in2[N] = {1,3,7,13,2,9,2,1,-10,-8};
  int out[N] ;
  cl::sycl::buffer<int, 1> in1_buf(&in1[0], cl::sycl::range<1>(N));
  cl::sycl::buffer<int, 1> in2_buf(&in2[0], cl::sycl::range<1>(N));
  cl::sycl::buffer<int, 1> out_buf(&out[0], cl::sycl::range<1>(N));
 
  binary_func(out_buf, in1_buf, in2_buf, N,
	  [=](int a, int b)->int{return a+b;});

 
 return 0; 
}

  


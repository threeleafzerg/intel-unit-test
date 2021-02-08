#pragma once

#include <iostream>
#include <CL/sycl.hpp>

using namespace cl::sycl;

template <int ADims, int BDims, int CDims, int DDims> 
struct kernel_name {};

cl::sycl::device getGPUDevice() {
  auto plaform_list = cl::sycl::platform::get_platforms();
  for(const auto& platform : plaform_list){
    auto device_list = platform.get_devices();
    for(const auto& device : device_list){
      if (device.is_gpu()) {
        std::cout << device.get_info<cl::sycl::info::device::name>() << std::endl;
        return device;
      }
    }
  }
  std::cout << "No GPU Device" << std::endl;
  exit(1);
}

cl::sycl::queue& getQueue() {
  static queue sycl_queue(getGPUDevice());
  return sycl_queue;
}

template <int ADims, int BDims, int CDims, int DDims>
void launchKernel() {
  int tensor_size[] = {1};
  {
    cl::sycl::buffer<int, 1> size_buf(tensor_size, 1);
    queue& sycl_queue = getQueue();
    sycl_queue.submit([&](cl::sycl::handler &cgh) {
      auto acc = size_buf.get_access<cl::sycl::access::mode::read_write>(cgh);
      cgh.single_task<class kernel_name<ADims, BDims, CDims, DDims>>([=]() {
        acc[0] = acc[0] * ADims * BDims * CDims * DDims;
      });
    });
    sycl_queue.wait_and_throw();
  }
  std::cout << "tensor_size[0] = " << tensor_size[0] << std::endl;
}


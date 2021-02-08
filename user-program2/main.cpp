#include <stdio.h>
#include <CL/sycl.hpp>
#include <iostream>


int foo(cl::sycl::queue queue) { 
  int wg_size = queue.get_device(). template get_info<cl::sycl::info::device::max_work_group_size>();
  printf("work group size = %d\n", wg_size);
  return 0;
}

void enumDevices(void) {
  auto platform_list = cl::sycl::platform::get_platforms();
  for(const auto& platform : platform_list){
    auto device_list = platform.get_devices();
    std::cout << "Find new platform:" << std::endl;
    std::cout << "Platform Name:" << platform.get_info<info::platform::name>()<< std::endl;
    std::cout << "Platform profile:" << platform.get_info<info::platform::profile>()<< std::endl;
    std::cout << "Platform version:" << platform.get_info<info::platform::version>()<< std::endl;
    std::cout << "Platform vendor:" << platform.get_info<info::platform::vendor>()<< std::endl;
    std::cout << "Platform extensions:" << platform.get_info<info::platform::extensions>()<< std::endl;
    for(const auto& device : device_list){
      if (device.is_cpu()) {
        std::cout << device.get_info<cl::sycl::info::device::name>() << std::endl;
        std::cout << device.get_info<cl::sycl::info::device::vendor>() << std::endl;
      }
    }
  }
}


int main(int argc, char **argv) {

  //cl::sycl::queue deviceQueue;

  //foo(deviceQueue);

  void enumDevices();

  return 0;
}


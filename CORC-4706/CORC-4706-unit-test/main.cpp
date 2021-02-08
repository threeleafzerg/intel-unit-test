#include <iostream>

#include <CL/sycl.hpp>

#include "interface.hpp"

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

int main(int argc, char **argv) {

  cl::sycl::queue deviceQueue;

  cl::sycl::device device(getGPUDevice());

  int i = 10;

  int reta = run_test_a(i, deviceQueue);

  int retb = run_test_b(i, device);

  if (reta == 2 * i && retb == 3 * i) {
    std::cout << "Unit Test Passed!" << std::endl;
  } else {
    std::cout << "Unit Test Failed!" << std::endl;
  }

	return 0;
}

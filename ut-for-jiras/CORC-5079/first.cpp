#include <CL/sycl.hpp>
#include <limits>
#include <numeric>
#include <assert.h>

using namespace cl::sycl;
template <typename T> void check(queue &Queue) {
  int arr[] = {10};
  {
    cl::sycl::buffer<int, 1> buf(arr, 1);
    Queue.submit([&](cl::sycl::handler &cgh) {
      auto acc = buf.get_access<cl::sycl::access::mode::read_write>(cgh);
      cgh.single_task<class hello_world>([=]() { 
        acc[0] *= 2; 
      });
    });
    Queue.wait_and_throw();
  }
  std::cout << "arr[0] = " << arr[0] << std::endl;
}

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

int main() {
  queue Queue(getGPUDevice());
  check<float>(Queue);
  std::cout << "Test passed." << std::endl;
}

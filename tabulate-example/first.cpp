#include "helper.hpp"
#include <CL/sycl.hpp>
#include <limits>
#include <numeric>
using namespace cl::sycl;

static const int ARR_SIZE = 10;

template <typename T>
struct NegOp {
public:
  T operator()(int index) { return (T)(-index); };
};

template <typename PtrType, typename UnaryOp> 
void sycl_tabulate(PtrType begin, PtrType end, UnaryOp unary_op) {
  for (int i = 0; (begin + i) != end; i++) {
    *(begin + i) = unary_op(i);
  }
}

void example(queue &Queue) {
  int arr[ARR_SIZE] = {0};
  {
    cl::sycl::buffer<int> buf(arr, 10);
    Queue.submit([&](cl::sycl::handler &cgh) {
      auto acc = buf.get_access<cl::sycl::access::mode::read_write, cl::sycl::access::target::global_buffer>(cgh);
      cgh.single_task<class tabulate_example>([=]() {
        auto ptr1 = acc.get_pointer();
        auto ptr2 = ptr1 + 10;
        sycl_tabulate(ptr1, ptr2, NegOp<int>());
      });
    });
    Queue.wait_and_throw();
  }
  for (int i = 0; i < 10; i++) {
    std::cout << arr[i] << std::endl;
  }
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
  if (!core_sg_supported(Queue.get_device())) {
    std::cout << "Skipping test\n";
    return 0;
  }

  example(Queue);
  //std::cout << "Test passed." << std::endl;
}

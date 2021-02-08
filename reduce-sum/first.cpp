#include <iostream>
#include <CL/sycl.hpp>


#include <SYCL/sycl_device_builtins.h>

using namespace std;
//using namespace cl::sycl::detail;
const int VAL = 10;

int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue;

	deviceQueue.submit([&](cl::sycl::handler &cgh) {
		int sg_size = 0;
		cgh.single_task<class kernel_a>([=]() {
//#ifdef __SYCL_DEVICE_ONLY_
		cl::sycl::detail::get_max_sub_group_size();
//#endif
		});
	}); 

	//cl::sycl::cl_uint(::_Z22get_max_sub_group_sizev());
	//int sg_size = 0;
  // sg_size = cl::sycl::detail::get_max_sub_group_size();
  //int sg_size = get_max_sub_group_size();

  //std::cout << "sg_size:" << sg_size << std::endl;

  return 0;
}

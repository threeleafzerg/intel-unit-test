#include <CL/sycl.hpp>  
#include <iostream>  
#include <algorithm>
#include <chrono>

#include <stdlib.h>

using namespace cl::sycl;  
// Size of the matrices 
//const size_t N = 2000;  
//const size_t M = 3000;  
//std::vector<cl::sycl::device> supported_devices;
//cl::sycl::gpu_selector selector;
//cl::sycl::device gDevice;

#if 0
void clear_sycl_devices() {
  supported_devices.clear();
}
#endif

#define N 10

int main(int argc, char **argv) { 
// Create a queue to work on 
#if 0
  queue myQueue; 
  // Create some 2D buffers of float for our matrices 
  buffer<float, 2> a(range<2>{N, M});  
  buffer<float, 2> b(range<2>{N, M});  
  buffer<float, 2> c(range<2>{N, M}); 
  // Launch a first asynchronous kernel to initialize a 
  myQueue.submit( [&](handler& cgh) { 
  // The kernel write a, so get a write accessor on it
  auto A = a.get_access<access::mode::write>(cgh);
  // Enqueue a parallel kernel iterating on a N*M 2D iteration space 
  cgh.parallel_for<class init_a>(range<2> {N, M}, [=](id<2> index) {
    A[index] = index[0] * 2 + index[1]; });
  });
  // Launch an asynchronous kernel to initialize b 
  myQueue.submit( [&](handler& cgh) { 
    // The kernel write b, so get a write accessor on it  
    auto B = b.get_access<access::mode::write>(cgh); 
    /* From the access pattern above, the SYCL runtime detect this 
      command_group is independant from the first one and can be  
      scheduled independently */ 
    // Enqueue a parallel kernel iterating on a N*M 2D iteration space 
    cgh.parallel_for<class init_b>(range<2> {N, M}, [=](id<2> index) { 
      B[index] = index[0] * 2014 + index[1] * 42; 
    }); 
  });
  // Launch an asynchronous kernel to compute matrix addition c = a + b 
  myQueue.submit( [&](handler& cgh) { 
  // In the kernel a and b are read, but c is written  
    auto A = a.get_access<access::mode::read>(cgh);  
    auto B = b.get_access<access::mode::read>(cgh);  
    auto C = c.get_access<access::mode::write>(cgh);  
    // From these accessors, the SYCL runtime will ensure that when  
    // this kernel is run, the kernels computing a and b completed  
    // Enqueue a parallel kernel iterating on a N*M 2D iteration space  
    cgh.parallel_for<class matrix_add>(range<2> {N, M}, [=](id<2> index) { 
      C[index] = A[index] + B[index]; });  
    }); 
    /* Ask an access to read c from the host-side. 
       This form implies access::target::host_buffer. The SYCL runtime 
       ensures that c is ready when the accessor is returned */ 
    auto C = c.get_access<access::mode::read>();  
    std::cout << std::endl << "Result:" << std::endl;  
    for (size_t i = 0; i < N; i++) {  
      for (size_t j = 0; j < M; j++) {  
        // Compare the result to the analytic value 
        if (C[i][j] != i * (2 + 2014) + j * (1 + 42)) { 
          std::cout << "Wrong value " << C[i][j] << " on element " << i << " " 
                    << j << std::endl; 
          exit(-1); 
        } 
      }  
    } 
    std::cout << "Good computation!" << std::endl; 
#endif

#if 0
    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0 ; i < 1000; i++) {
      queue myQueue;
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
    std::cout << "1000 sycl::queue took " << fp_ms.count() << "ms." << std::endl;


    //std::vector<cl::sycl::device> supported_devices;
    auto platform_list =cl::sycl::platform::get_platforms();
    for(const auto& platform : platform_list){
      auto device_list = platform.get_devices();
      auto platform_name = platform.template get_info<cl::sycl::info::platform::name>();
      for( auto device : device_list){
        if (device.is_gpu()) {
          std::cout << device.template get_info<cl::sycl::info::device::vendor>() << std::endl;
          std::cout << device.template get_info<cl::sycl::info::device::name>() << std::endl;
          std::cout << device.template get_info<cl::sycl::info::device::max_compute_units>() << std::endl;
          //supported_devices.push_back(device);
        }
      }
    }
#endif
   
#if 1
//    cl::sycl::device gDevice(selector);
//    supported_devices.push_back(gDevice);
//    std::cout << gDevice.template get_info<cl::sycl::info::device::vendor>() << " gDevice." << std::endl;
//    std::cout << supported_devices[0].template get_info<cl::sycl::info::device::vendor>() << " supported_devices."  << std::endl;
//    supported_devices.clear();
//    atexit(clear_sycl_devices);
#endif
//   std::vector<cl::sycl::queue> supported_queues;

  queue gQueue;
  int a[N] = {1,3,7,13,2,9,2,1,-10,-8};
//    auto device = gQueue.get_device();
//    std::cout << device.template get_info<cl::sycl::info::device::vendor>() << " device"<< std::endl;
//    supported_queues.push_back(gQueue);
    
//      std::cout << gDevice.template get_info<cl::sycl::info::device::vendor>() << std::endl;
  cl::sycl::buffer<int, 1> a_buf(&a[0], cl::sycl::range<1>(N));
  gQueue.submit([&](cl::sycl::handler &cgh) {
    constexpr auto a_mode = cl::sycl::access::mode::read_write;
    auto a_accessor = a_buf.get_access<a_mode>(cgh);
    cgh.parallel_for<class hello_world>(cl::sycl::range<1>(N),
                                        [=](cl::sycl::id<1> i) {
                                        a_accessor[i] *= 2;
                                        });
  });
   
  return 0; 
}

  


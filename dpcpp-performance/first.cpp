#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <assert.h>
#include <utility>
#include <tuple>
#include "Array.hpp"
#include "C++17.hpp"
#include "FunctionTraits.h"
#include "SYCL.h"

using namespace std;

// According to OpenCL C spec, the format string must be in constant address
// space
#ifdef __SYCL_DEVICE_ONLY__
#define CONSTANT __attribute__((opencl_constant))
#else
#define CONSTANT
#endif


using in_ptr_t = typename cl::sycl::global_ptr<char>::pointer_t;

#define MAX_DIMS 25

template <typename traits, typename ptr_t, typename index_t, std::size_t... I>
typename traits::ArgsTuple
dereference_impl(ptr_t data[], const index_t strides[], int i, c10::guts::index_sequence<I...>) {
    return std::make_tuple(*(typename traits::template arg<I>::type*)(data[I] + i * strides[I])...);
}

template <typename traits, typename ptr_t, typename index_t>
typename traits::ArgsTuple
dereference(ptr_t data[], const index_t strides[], int i) {
    using Indices = c10::guts::make_index_sequence<traits::arity>;
      return dereference_impl<traits>(data, strides, i, Indices{});
}

struct BufferInfo {
	int ndim;
	std::array<int, 1> strides;
	std::array<int, 1> shape;
};

template <typename IndexType = uint32_t>
struct SyclOffsetCal {
  int dims;
  // Make the information to be basic data types to avoid compiler issue.
  IndexType sizes[MAX_DIMS];
  IndexType strides[MAX_DIMS];

  IndexType get(IndexType linear_idx) const {
    IndexType offset = 0;

    for (int dim = 0; dim < dims; ++dim) {
      // Make the code as naive as possible.
      offset += (linear_idx % sizes[dim]) * strides[dim];
      linear_idx = linear_idx / sizes[dim];
    }
    return offset;
  }
};

template<typename IndexType>
static SyclOffsetCal<IndexType> make_offset_calculator(const BufferInfo& info) {
  SyclOffsetCal<IndexType> offset;
  auto dims = info.ndim;
  offset.dims = dims;
  auto strides = info.strides;
  auto sizes = info.shape;
  for (int i = 0; i < dims; i++) {
    offset.sizes[i] = sizes[i];
    offset.strides[i] = strides[i];
  }
  return offset;
}

static void handle_exception(const cl::sycl::exception &e) {
  std::cout << "SYCL exception caught: " << e.what() << std::endl;
}

static void handle_exceptions(const cl::sycl::exception_list &l) {
  std::cout << "SYCL exception handler called\n";

  for (cl::sycl::exception_ptr_class const& eptr : l) {
    try {
      std::rethrow_exception(eptr);
    }
    catch (cl::sycl::exception const& e) {
      std::cout << "Caught asynchronous SYCL exception: " << e.what() << std::endl;
    }
  }
}

void fill_data(float *arr, int num, float data) {
  for (int i = 0; i < num; i++) {
    arr[i] = data;
  }
}

template< class func_t >
void run_add_test(cl::sycl::queue &deviceQueue, func_t op) {
    try {
      using traits = function_traits<func_t>;
      using ret_t = typename traits::result_type;
      int num = 56;
      //int num = 256 * 256;
      float *host_a = new float[num];
      float *host_b = new float[num];
      float *host_c = new float[num];
      fill_data(host_a, num, 1.1f);
      fill_data(host_b, num, 2.1f);
      fill_data(host_c, num, 5.0f);
			BufferInfo info;
			info.ndim = 1;
			info.strides = {1};
			info.shape = {num};
			
      {
        cl::sycl::buffer<float, 1> buf_a(host_a, cl::sycl::range<1>(num));
        cl::sycl::buffer<float, 1> buf_b(host_b, cl::sycl::range<1>(num));
        cl::sycl::buffer<float, 1> buf_c(host_c, cl::sycl::range<1>(num));
        deviceQueue.submit([&](cl::sycl::handler &cgh) {
          auto acc_a = buf_a.get_access<cl::sycl::access::mode::read_write>(cgh);
          auto acc_b = buf_b.get_access<cl::sycl::access::mode::read_write>(cgh);
          auto acc_c = buf_c.get_access<cl::sycl::access::mode::read_write>(cgh);
          auto acc_d = buf_c.get_access<cl::sycl::access::mode::read_write>(cgh);
					SyclOffsetCal<uint32_t> __off_0 = make_offset_calculator<uint32_t>(info);
					SyclOffsetCal<uint32_t> __off_1 = make_offset_calculator<uint32_t>(info);
					SyclOffsetCal<uint32_t> __off_2 = make_offset_calculator<uint32_t>(info);
					SyclOffsetCal<uint32_t> __off_3 = make_offset_calculator<uint32_t>(info);
					
					using in_ptr_t = typename cl::sycl::global_ptr<char>::pointer_t;
          cgh.parallel_for<class kernel_add>(cl::sycl::range<1>(num), [=](cl::sycl::item<1> item_id) { 
						static const CONSTANT char format_hello_world[] = "Hello, World!\n";
						cl::sycl::intel::experimental::printf(format_hello_world);
						auto out_ptr = (in_ptr_t)acc_c.get_pointer().get();
						Array<in_ptr_t, 3> in_ptr;
						Array<uint32_t, 4> offsets;	

						in_ptr[0] = (in_ptr_t)acc_a.get_pointer().get();
						in_ptr[1] = (in_ptr_t)acc_b.get_pointer().get();
						in_ptr[2] = (in_ptr_t)acc_d.get_pointer().get();

            auto idx = item_id.get_id(0);

						//offsets[0] = idx * 4;	
						//offsets[1] = idx * 4;	
						//offsets[2] = idx * 4;	
						//offsets[3] = idx * 4;	

						offsets[0] = __off_0.get(idx) * 4;	
						offsets[1] = __off_1.get(idx) * 4;	
						offsets[2] = __off_2.get(idx) * 4;	
						offsets[3] = __off_3.get(idx) * 4;	

            using arg0_t = typename traits::template arg<0>::type;
            using arg_ptr_t = typename cl::sycl::global_ptr<arg0_t>::pointer_t;

            ret_t* out = (ret_t *)(out_ptr + offsets[0]);
            auto in_ptr0 = (arg_ptr_t)(in_ptr[0] + offsets.data[1]);
            auto in_ptr1 = (arg_ptr_t)(in_ptr[1] + offsets.data[2]);
            *out = op(*in_ptr0, *in_ptr1);

#if 0
						ret_t* out = (ret_t *)(out_ptr + offsets[0]);
						*out = c10::guts::apply(op, dereference<traits>(
              			&in_ptr.data[0],
              			&offsets.data[1],
              			1));
#endif
          });
        });
        deviceQueue.wait_and_throw();
      }
      std::cout << "host_c[0] = " << host_c[num-2] << std::endl; 
      std::cout << "host_c[0] = " << host_c[num-1] << std::endl; 
      std::cout << "host_c[0] = " << host_c[1000] << std::endl; 
    }
    catch (cl::sycl::exception &e) {
      handle_exception(e);
    }
}

int main(int argc, char **argv) {
  cl::sycl::queue deviceQueue(handle_exceptions);
  float alpha = 2.0;
	auto add_func = [=](float a, float b) -> float {
        return a + alpha * b;
  };
  run_add_test(deviceQueue, add_func);
  return 0;
}


#include <iostream>
#include <CL/sycl.hpp>
#include <stdlib.h>
#include <cmath>

using namespace std;
using namespace cl::sycl;

namespace hello {
namespace world {

namespace {
template<typename T>
struct randomFiller {};

template <typename T>
 void randomFill2(buffer<int, 1>& buf, queue& myQueue) { 
	myQueue.submit([&](handler& cgh) {
	auto ptr = buf.get_access<access::mode::read_write>(cgh); 
  auto a = cl::sycl::accessor<int, 1, access::mode::read_write, cl::sycl::access::target::local>(10, cgh);
  cgh.parallel_for<randomFiller<T>> (cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256)),
                                  [=](cl::sycl::nd_item<1> item_id) {
                                      if (item_id.get_local_linear_id() != 0) { 
                                        ptr[item_id.get_local_linear_id()] = 100;
                                      }
                                  });
	});
}
} //end of anonymous

inline void randomFill(buffer<int, 1>& buf, queue& myQueue) {

#define HANDLE_RANDOM_FILL1(a,b) randomFill2<float>((a), (b))
#define HANDLE_RANDOM_FILL2(a,b) randomFill2<int>((a), (b))


//  randomFill2(buf, myQueue);
  HANDLE_RANDOM_FILL1(buf, myQueue);
  HANDLE_RANDOM_FILL2(buf, myQueue);


#undef HANDLE_RANDOM_FILL
}

} //end of world
} //end of hello




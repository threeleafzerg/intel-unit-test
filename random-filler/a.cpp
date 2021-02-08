#include "a.hpp"

void kernel3(queue Queue) {
  Queue.submit([&](cl::sycl::handler &cgh){
    FloatRandomFiller uniform_rnd_filler;
    auto num_work_items = cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256));
    cgh.parallel_for(num_work_items, uniform_rnd_filler);
  });
}

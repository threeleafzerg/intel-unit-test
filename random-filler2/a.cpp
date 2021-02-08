#include "a.hpp"

void kernel3(queue Queue) {
  Queue.submit([&](cl::sycl::handler &cgh){
    FloatRandomFiller uniform_rnd_filler;
    auto num_work_items = cl::sycl::nd_range<1>(cl::sycl::range<1>(256), cl::sycl::range<1>(256));
    cgh.parallel_for<class kernel3>(num_work_items, [=] (cl::sycl::nd_item<1> nd_item){
      uniform_rnd_filler(nd_item);
    });
  });
}

#include <CL/sycl.hpp>
#include <limits>
#include <numeric>

using namespace cl::sycl;

template<typename T>
class MTRandomEngine {
public:
  int generate_random_numbers(const int& gid) { return gid+1; };
};

class FloatRandomFiller;

class FloatRandomFiller : public MTRandomEngine<float> {
public:
  void operator()(nd_item<1> item) {
    int gid = item.get_global_linear_id();
    int ret = generate_random_numbers(gid);
  }
};

void kernel3(queue Queue); 

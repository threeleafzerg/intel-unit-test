#include <CL/sycl.hpp>
#include <vector>
#include <assert.h>
#include <stdio.h>

using namespace cl::sycl;

constexpr info::partition_property partition_by_affinity =
	info::partition_property::partition_by_affinity_domain;

constexpr info::partition_affinity_domain next_partitionable =
	info::partition_affinity_domain::next_partitionable;

int main() {
	gpu_selector s;
  platform p(s);

  // gpu[0] is the first card
  // gpu[1] is the second card
  std::vector<device> gpu = p.get_devices(info::device_type::gpu);

  auto prop_vec = gpu[0].get_info<info::device::partition_properties>();
  std::cout << "prop vec size:" << prop_vec.size() << std::endl;
  std::cout << "prop_vec[0]=" << static_cast<int>(prop_vec[0]) << std::endl;
  std::cout << "__SYCL_COMPILER_VERSION=" << __SYCL_COMPILER_VERSION << std::endl;
#if 1
  // All tiles of gpu0
  std::vector<device> gpu0tiles =
	  gpu[0].create_sub_devices<partition_by_affinity>(next_partitionable);
  
  printf("sub devices number:%zu\n", gpu0tiles.size());
  // A queue bound to a tile0 of gpu0
  queue q0_0(gpu0tiles[0]);

  // A queue bound to all tiles of gpu0
  queue q0(gpu[0]);
#endif
}

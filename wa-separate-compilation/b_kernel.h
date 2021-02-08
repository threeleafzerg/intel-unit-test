// This is auto-generated SYCL integration header.

#include <CL/sycl/detail/defines.hpp>
#include <CL/sycl/detail/kernel_desc.hpp>

// Forward declarations of templated kernel function types:
class kernel_b;

__SYCL_INLINE_NAMESPACE(cl) {
namespace sycl {
namespace detail {

// names of all kernels defined in the corresponding source
static constexpr
const char* const kernel_names[] = {
  "_ZTS8kernel_b"
};

// array representing signatures of all kernels defined in the
// corresponding source
static constexpr
const kernel_param_desc_t kernel_signatures[] = {
  //--- _ZTS8kernel_b
  { kernel_param_kind_t::kind_accessor, 4062, 0 },

};

// indices into the kernel_signatures array, each representing a start of
// kernel signature descriptor subarray of the kernel_signatures array;
// the index order in this array corresponds to the kernel name order in the
// kernel_names array
static constexpr
const unsigned kernel_signature_start[] = {
  0 // _ZTS8kernel_b
};

// Specializations of KernelInfo for kernel function types:
template <> struct KernelInfo<::kernel_b> {
  DLL_LOCAL
  static constexpr const char* getName() { return "_ZTS8kernel_b"; }
  DLL_LOCAL
  static constexpr unsigned getNumParams() { return 1; }
  DLL_LOCAL
  static constexpr const kernel_param_desc_t& getParamDesc(unsigned i) {
    return kernel_signatures[i+0];
  }
};

} // namespace detail
} // namespace sycl
} // __SYCL_INLINE_NAMESPACE(cl)


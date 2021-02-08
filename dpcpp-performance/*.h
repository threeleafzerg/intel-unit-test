// This is auto-generated SYCL integration header.

#include <CL/sycl/detail/defines.hpp>
#include <CL/sycl/detail/kernel_desc.hpp>

// Forward declarations of templated kernel function types:
class kernel_add;

__SYCL_INLINE_NAMESPACE(cl) {
namespace sycl {
namespace detail {

// names of all kernels defined in the corresponding source
static constexpr
const char* const kernel_names[] = {
  "_ZTSZZ12run_add_testIZ4mainE3$_0EvRN2cl4sycl5queueET_ENKUlRNS2_7handlerEE_clES7_E10kernel_add"
};

// array representing signatures of all kernels defined in the
// corresponding source
static constexpr
const kernel_param_desc_t kernel_signatures[] = {
  //--- _ZTSZZ12run_add_testIZ4mainE3$_0EvRN2cl4sycl5queueET_ENKUlRNS2_7handlerEE_clES7_E10kernel_add
  { kernel_param_kind_t::kind_accessor, 4062, 0 },
  { kernel_param_kind_t::kind_accessor, 4062, 32 },
  { kernel_param_kind_t::kind_accessor, 4062, 64 },
  { kernel_param_kind_t::kind_accessor, 4062, 96 },
  { kernel_param_kind_t::kind_std_layout, 204, 128 },
  { kernel_param_kind_t::kind_std_layout, 204, 332 },
  { kernel_param_kind_t::kind_std_layout, 204, 536 },
  { kernel_param_kind_t::kind_std_layout, 204, 740 },
  { kernel_param_kind_t::kind_std_layout, 4, 944 },

};

// indices into the kernel_signatures array, each representing a start of
// kernel signature descriptor subarray of the kernel_signatures array;
// the index order in this array corresponds to the kernel name order in the
// kernel_names array
static constexpr
const unsigned kernel_signature_start[] = {
  0 // _ZTSZZ12run_add_testIZ4mainE3$_0EvRN2cl4sycl5queueET_ENKUlRNS2_7handlerEE_clES7_E10kernel_add
};

// Specializations of KernelInfo for kernel function types:
template <> struct KernelInfo<class kernel_add> {
  DLL_LOCAL
  static constexpr const char* getName() { return "_ZTSZZ12run_add_testIZ4mainE3$_0EvRN2cl4sycl5queueET_ENKUlRNS2_7handlerEE_clES7_E10kernel_add"; }
  DLL_LOCAL
  static constexpr unsigned getNumParams() { return 9; }
  DLL_LOCAL
  static constexpr const kernel_param_desc_t& getParamDesc(unsigned i) {
    return kernel_signatures[i+0];
  }
};

} // namespace detail
} // namespace sycl
} // __SYCL_INLINE_NAMESPACE(cl)


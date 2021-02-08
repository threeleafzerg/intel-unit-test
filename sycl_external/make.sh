#!/bin/bash
export SYCL_ROOT=/home/zhouhaiy/tool_chain/compiler-nightly-build/compiler-nightly-0303/compiler/linux
export LD_LIBRARY_PATH=${SYCL_ROOT}/lib:${SYCL_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
make -j4

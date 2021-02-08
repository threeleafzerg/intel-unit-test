#!/bin/bash


export SYCL_ROOT=/home/zhouhaiy/workspace/llvm/latest2/build
export LD_LIBRARY_PATH=${SYCL_ROOT}/lib:${SYCL_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}

./test

#!/bin/bash


export ONE_API_ROOT=/home/zhouhaiy/tool_chain/oneapi/beta01/inteloneapi
export SYCL_ROOT=${ONE_API_ROOT}/compiler/latest/linux
export LD_LIBRARY_PATH=${SYCL_ROOT}/lib:${SYCL_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}

./test

#!/bin/bash
export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/oneapi/beta6/inteloneapi/compiler/latest/linux
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/lib:/usr/local/lib:${DPC_CPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
#export SYCL_DUMP_IMAGES=1 
#export SYCL_BE=PI_OPENCL
#export SYCL_PI_TRACE=-1
./first.exe 2>&1 | tee run.log

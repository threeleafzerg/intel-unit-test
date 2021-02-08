#!/bin/bash

export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/compiler/compiler-nightly-0427/compiler/linux
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/lib:${DPC_CPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
#export SYCL_DUMP_IMAGES=1 
export OverrideDefaultFP64Settings=1
export IGC_EnableDPEmulation=1
./test 2>&1 | tee run.log

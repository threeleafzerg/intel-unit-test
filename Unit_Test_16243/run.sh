#!/bin/bash

export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/compiler/mingxiao/2021.1-beta09/linux
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/lib:${DPC_CPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
#export SYCL_DUMP_IMAGES=1 
./test 2>&1 | tee run.log

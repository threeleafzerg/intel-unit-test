#!/bin/bash
export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/fix_mem_leak
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/lib:${LD_LIBRARY_PATH}
#export SYCL_DUMP_IMAGES=1 
./first.exe

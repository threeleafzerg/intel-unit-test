#!/bin/bash
#export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/dpcpp_compiler
export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/computecpp
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/lib:/opt/intel/opencl/SDK/lib64/
./first.exe

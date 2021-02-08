#!/bin/bash
#export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/dpcpp_compiler
export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/computecpp/ComputeCpp-CE-1.0.3-Ubuntu-16.04-x86_64
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/lib:/opt/intel/opencl/SDK/lib64/
./first.exe

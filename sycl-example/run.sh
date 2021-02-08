#!/bin/bash
COMPUTE_CPP_ROOT=/home/zhouhaiy/tool_chain/computecpp
OPENCL_ROOT=/opt/intel/opencl
export LD_LIBRARY_PATH=${COMPUTE_CPP_ROOT}/lib:/opt/intel/opencl:${LD_LIBRARY_PATH}
./first.exe

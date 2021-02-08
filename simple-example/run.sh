#!/bin/bash
COMPUTE_CPP_ROOT=/home/sunbear/zhouhaiy/computecpp/ComputeCpp-CE-1.0.3-Ubuntu-16.04-x86_64
OPENCL_ROOT=/opt/intel/opencl
export LD_LIBRARY_PATH=${COMPUTE_CPP_ROOT}/lib:/opt/intel/opencl:${LD_LIBRARY_PATH}
./first.exe

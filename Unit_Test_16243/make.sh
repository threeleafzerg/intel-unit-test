#!/bin/bash
#export DPCPP_ROOT=/home/zhouhaiy/tool_chain/compiler/compiler-nightly-0427/compiler/linux
export DPCPP_ROOT=/home/zhouhaiy/tool_chain/compiler/mingxiao/2021.1-beta09/linux
export LD_LIBRARY_PATH=${DPCPP_ROOT}/lib:${DPCPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
make -j6

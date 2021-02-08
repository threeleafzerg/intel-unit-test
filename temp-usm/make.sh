#!/bin/bash
#export DPCPP_ROOT=/home/zhouhaiy/tool_chain/compiler/compiler-nightly-0427/compiler/linux
#export DPCPP_ROOT=/home/zhouhaiy/tool_chain/compiler-nightly-build/compiler-nightly-0506/compiler/linux
export DPCPP_ROOT=/home/guizili/dpcpp/compiler/2020-05-20/dpcpp_compiler
export LD_LIBRARY_PATH=${DPCPP_ROOT}/lib:${DPCPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
make -j6

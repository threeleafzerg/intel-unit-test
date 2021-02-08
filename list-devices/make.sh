#!/bin/bash
export DPCPP_ROOT=/home/zhouhaiy/tool_chain/oneapi/beta6/inteloneapi/compiler/latest/linux
export LD_LIBRARY_PATH=${DPCPP_ROOT}/lib:${DPCPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
make -j6

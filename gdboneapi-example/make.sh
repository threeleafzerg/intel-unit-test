#!/bin/bash

export ONE_API_ROOT=/home/zhouhaiy/tool_chain/oneapi/beta04/inteloneapi
export DPC_CPP_ROOT=${ONE_API_ROOT}/compiler/latest/linux
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}

make -j4

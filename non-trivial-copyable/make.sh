#!/bin/bash

export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/fix_mem_leak
export LD_LIBRARY_PATH=${DPC_CPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}

make -j4

#!/bin/bash
export DPC_CPP_ROOT=/home/zhouhaiy/tool_chain/dpcpp_compiler
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${DPC_CPP_ROOT}/lib
./first.exe

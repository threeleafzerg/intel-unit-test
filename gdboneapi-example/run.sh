#!/bin/bash


export ONE_API_ROOT=/home/zhouhaiy/tool_chain/oneapi/beta04/inteloneapi
export SYCL_ROOT=${ONE_API_ROOT}/compiler/latest/linux
export LD_LIBRARY_PATH=${SYCL_ROOT}/lib:${SYCL_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
export SYCL_PROGRAM_BUILD_OPTIONS="-g -cl-opt-disable"
gdb-oneapi ./first.exe
#valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./first.exe 2>&1 | tee valgrind.out


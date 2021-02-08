#!/bin/bash


export SYCL_ROOT=/home/zhouhaiy/tool_chain/dpcpp_build
export LD_LIBRARY_PATH=${SYCL_ROOT}/lib:${SYCL_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
#SYCL_DUMP_IMAGES=1 ./first.exe
SYCL_DUMP_IMAGES=1 ./test_half
#valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./first.exe 2>&1 | tee valgrind.out


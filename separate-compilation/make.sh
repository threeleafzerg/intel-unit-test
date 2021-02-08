#!/bin/bash

set -x
export DPCPP_ROOT=/home/zhouhaiy/workspace/llvm/latest2/build
export PATH=${DPCPP_ROOT}/bin:${PATH}
export LD_LIBRARY_PATH=${DPCPP_ROOT}/lib:${LD_LIBRARY_PATH}
clang++ -fsycl a.cpp b.cpp -c -fPIC
g++-7 main.cpp -c -fPIC
clang++ -fPIC -fsycl -fsycl-link a.o b.o -o dev.o
ar -rcs libuser.a  a.o b.o dev.o 
g++-7 main.o -L${DPCPP_ROOT}/lib -L. -lOpenCL -Wl,--whole-archive -luser -Wl,--no-whole-archive -lsycl
#g++ main.o a.o b.o dev.o -L/home/zhouhaiy/tool_chain/fix_mem_leak/lib -lOpenCL -lsycl

#!/bin/bash

set -x

export DPCPP_ROOT=/home/zhouhaiy/tool_chain/compiler/compiler-nightly-0427/compiler/linux
g++ -I${DPCPP_ROOT}/include/sycl -o main.o -c main.cpp
g++ main.o -o test -L${DPCPP_ROOT}/lib -lOpenCL


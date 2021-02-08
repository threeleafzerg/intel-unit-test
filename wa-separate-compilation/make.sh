#!/bin/bash

set -x
export DPCPP_ROOT=/home/zhouhaiy/tool_chain/compiler/compiler-nightly-0427/compiler/linux
export PATH=${DPCPP_ROOT}/bin:${PATH}
export LD_LIBRARY_PATH=${DPCPP_ROOT}/lib:${DPCPP_ROOT}/compiler/lib/intel64_lin:${LD_LIBRARY_PATH}
### Separate compilation
dpcpp -fsycl a.cpp b.cpp -c -fPIC
dpcpp -fsycl-device-only -Xclang -fsycl-int-header=a_kernel.h a.cpp
dpcpp -fsycl-device-only -Xclang -fsycl-int-header=b_kernel.h b.cpp
g++ -c a.cpp -o a_host.o -include a_kernel.h -I ${DPCPP_ROOT}/include/sycl
g++ -c b.cpp -o b_host.o -include b_kernel.h -I ${DPCPP_ROOT}/include/sycl

### Normal Compilation
g++ main.cpp -c -fPIC

### Linkage Stage
### Link Step 1
dpcpp -fPIC -fsycl -fsycl-link a.o b.o -o dev.o

### Link Step 2
g++ main.o a_host.o b_host.o dev.o -L${DPCPP_ROOT}/lib -lOpenCL -lsycl

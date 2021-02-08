
DPC_CPP_ROOT := /home/zhouhaiy/tool_chain/compiler-nightly-build/dpcpp_compiler

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

LDFLAGS := -L$(OPENCL_ROOT) -lOpenCL -L${DPC_CPP_ROOT}/lib -lsycl 

all: test

main.o: main.cpp
	$(SYCLCXX) -fPIC -fsycl -I $(DPC_CPP_ROOT)/include/sycl -c main.cpp -fsycl

a.o : a.cpp
	$(SYCLCXX) -o a.o -c a.cpp

test : main.o a.o
	$(SYCLCXX) main.o a.o -o test $(LDFLAGS)

clean:
	rm -f test main.o a.o 

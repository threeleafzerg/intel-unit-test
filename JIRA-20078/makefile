
DPC_CPP_ROOT := /home/zhouhaiy/tool_chain/compiler-nightly-build/compiler-nightly-0506/compiler/linux

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

CXXFLAGS := -I $(DPC_CPP_ROOT)/include/sycl -I $(OPENCL_ROOT)/include -fsycl

LDFLAGS := -L $(OPENCL_ROOT)/lib -L $(DPC_CPP_ROOT)/lib  -lOpenCL -fsycl

all: test

main.o: main.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c main.cpp

test: main.o
	$(SYCLCXX) main.o  -o test  $(LDFLAGS)

clean:
	rm -f test main.o

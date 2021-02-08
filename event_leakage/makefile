
DPC_CPP_ROOT := /home/zhouhaiy/tool_chain/compiler-nightly-build/20200716/compiler/linux

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

CXXFLAGS := -I $(DPC_CPP_ROOT)/include/sycl -I $(OPENCL_ROOT)/include -fsycl

LDFLAGS := -L $(OPENCL_ROOT)/lib -L $(DPC_CPP_ROOT)/lib  -lOpenCL -fsycl

all: first.exe

first.o: first.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c first.cpp

first.exe : first.o
	$(SYCLCXX) first.o  -o first.exe $(LDFLAGS)

clean:
	rm -f first.exe first.o

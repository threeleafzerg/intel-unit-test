

DPC_CPP_ROOT := /home/zhouhaiy/tool_chain/fix_mem_leak

OPENCL_ROOT := /opt/intel/opencl

#SYCLCXX := $(COMPUTE_CPP_ROOT)/bin/compute++ 

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

#CXX := g++

CXXFLAGS := -I $(DPC_CPP_ROOT)/lib/clang/11.0.0/include -I $(OPENCL_ROOT)/include -fsycl

LDFLAGS := -L $(OPENCL_ROOT)/lib -L $(DPC_CPP_ROOT)/lib  -lOpenCL -fsycl

all: first.exe

first.o: first.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c first.cpp

first.exe : first.o
	$(SYCLCXX) first.o  -o first.exe $(LDFLAGS)

clean:
	rm -f first.exe first.o

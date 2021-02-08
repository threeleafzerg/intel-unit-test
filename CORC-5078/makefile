
#COMPUTE_CPP_ROOT := /home/sunbear/zhouhaiy/computecpp/ComputeCpp-CE-1.0.3-Ubuntu-16.04-x86_64

DPC_CPP_ROOT := /home/zhouhaiy/tool_chain/dpcpp_compiler

OPENCL_ROOT := /home/zhouhaiy/tool_chain/dpcpp_compiler

#SYCLCXX := $(COMPUTE_CPP_ROOT)/bin/compute++ 

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

#CXX := g++

CXXFLAGS := -I $(DPC_CPP_ROOT)/include -I $(OPENCL_ROOT)/include

LDFLAGS := -L $(OPENCL_ROOT)/lib -lOpenCL -L $(DPC_CPP_ROOT)/lib -lsycl

all: libfirst.so

first.o: first.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c first.cpp

libfirst.so : first.o
	$(SYCLCXX) -shared $<  -o $@ $(LDFLAGS)

clean:
	rm -f libfirst.so first.o

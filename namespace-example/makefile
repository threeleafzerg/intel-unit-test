
#COMPUTE_CPP_ROOT := /home/sunbear/zhouhaiy/computecpp/ComputeCpp-CE-1.0.3-Ubuntu-16.04-x86_64

DPC_CPP_ROOT := /home/sunbear/intel/dpcpp_bundle_1.0_prealpha_u8_020/dpcpp_compiler

OPENCL_ROOT := /opt/intel/opencl

#SYCLCXX := $(COMPUTE_CPP_ROOT)/bin/compute++ 

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

#CXX := g++

CXXFLAGS := -I $(DPC_CPP_ROOT)/include -I $(OPENCL_ROOT)/include -fsycl

LDFLAGS := -L $(OPENCL_ROOT)/lib -lOpenCL -fsycl

all: first.exe

first.o: first.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c first.cpp

first.exe : first.o 
	$(SYCLCXX) first.o -o first.exe $(LDFLAGS)

clean:
	rm -f first.exe first.o

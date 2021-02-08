
COMPUTE_CPP_ROOT := /home/zhouhaiy/tool_chain/computecpp

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(COMPUTE_CPP_ROOT)/bin/compute++ 

CXX := g++

COMPUTECPP_DEVICE_COMPILER_FLAGS := -O2 -mllvm -inline-threshold=1000 -sycl -intelspirmetadata -sycl-target spir64 -std=c++11  -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include

CXXFLAGS := -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include

LDFLAGS := -L$(COMPUTE_CPP_ROOT)/lib -lComputeCpp -L$(OPENCL_ROOT) -lOpenCL

all: first.exe

first.sycl: first.cpp
	${SYCLCXX} ${COMPUTECPP_DEVICE_COMPILER_FLAGS} -c first.cpp

first.o: first.sycl first.cpp
	$(SYCLCXX) -std=c++11 -c -fPIC first.cpp -include first.sycl $(CXXFLAGS)

first.exe : first.o
	$(SYCLCXX) first.o  -o first.exe $(LDFLAGS)

clean:
	rm -f first.sycl first.exe first.o *.bc

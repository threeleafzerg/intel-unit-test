
DPC_CPP_ROOT := /home/sunbear/intel/data_parallel_cpp_1.0_pre_alpha_update_7_011/dpcpp

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++ -v 

CXX := g++

DPCCPP_DEVICE_COMPILER_FLAGS := -O2 -fsycl

#COMPUTECPP_DEVICE_COMPILER_FLAGS := -O2 -mllvm -inline-threshold=1000 -sycl -intelspirmetadata -sycl-target spir64 -std=c++11 -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include -L$(COMPUTE_CPP_ROOT)/lib -lComputeCpp -L$(OPENCL_ROOT) -lOpenCL

#CXXFLAGS := -I $(OPENCL_ROOT)/include

LDFLAGS := -fsycl -lsycl -L$(OPENCL_ROOT) -lOpenCL
#LDFLAGS := -fsycl 

all: first.exe

first.o: first.cpp
	$(SYCLCXX) ${DPCCPP_DEVICE_COMPILER_FLAGS} -std=c++11 -fPIC -c first.cpp $(CXXFLAGS)

first.exe : first.o
	$(SYCLCXX) first.o ${LDFLAGS} -o first.exe

clean:
	rm -f first.exe first.o 

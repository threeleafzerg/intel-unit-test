
INTEL_SYCL_BUNDLE := 
INTEL_SYCL_BUNDLE_SYCL_INCLUDE := /home/sunbear/intel/data_parallel_cpp_1.0_pre_alpha_update_7_011/dpcpp/lib/clang/9.0.0/include

COMPUTE_CPP_ROOT := /home/sunbear/zhouhaiy/computecpp/ComputeCpp-CE-1.0.3-Ubuntu-16.04-x86_64

OPENCL_ROOT := /opt/intel/opencl

SYCL_LIB := mkl_sycl

SYCLCXX := $(COMPUTE_CPP_ROOT)/bin/compute++ 

#CXX := $(COMPUTE_CPP_ROOT)/bin/compute++
#CXX := g++

#COMPUTECPP_DEVICE_COMPILER_FLAGS := -O2 -mllvm -inline-threshold=1000 -sycl -intelspirmetadata -sycl-target spir64 -std=c++11  -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include
#COMPUTECPP_DEVICE_COMPILER_FLAGS := -O2 -mllvm -inline-threshold=1000 -sycl -intelspirmetadata -sycl-target spir64 -std=c++11  -I $(INTEL_SYCL_BUNDLE)/include -I $(OPENCL_ROOT)/include

#COMPUTECPP_DEVICE_COMPILER_FLAGS := -O2 -mllvm -inline-threshold=1000 -sycl -intelspirmetadata -sycl-target spir64 -std=c++11 -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include -L$(COMPUTE_CPP_ROOT)/lib -lComputeCpp -L$(OPENCL_ROOT) -lOpenCL

#CXXFLAGS := -I $(INTEL_SYCL_BUNDLE_SYCL_INCLUDE) -I $(OPENCL_ROOT)/include -I ${INTEL_SYCL_BUNDLE}/mkl/include
CXXFLAGS := -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include -I ${INTEL_SYCL_BUNDLE}/mkl/include

#LDFLAGS := -L$(INTEL_SYCL_BUNDLE)/dpcpp/lib -lsycl -fPIC  -L$(OPENCL_ROOT) -lOpenCL -L${INTEL_SYCL_BUNDLE}/mkl/lib/intel64_lin -lmkl_sycl -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm
LDFLAGS := -L$(COMPUTE_CPP_ROOT)/lib -lComputeCpp -L$(OPENCL_ROOT) -lOpenCL -L${INTEL_SYCL_BUNDLE}/mkl/lib/intel64_lin -lmkl_sycl

all: gemm

gemm.o: gemm.cpp
	$(SYCLCXX) -std=c++11 -c -fPIC gemm.cpp $(CXXFLAGS)

gemm : gemm.o
	$(SYCLCXX) gemm.o  -o gemm $(LDFLAGS)

clean:
	rm -f gemm.o gemm

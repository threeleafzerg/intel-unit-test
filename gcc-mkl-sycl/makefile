
INTEL_SYCL_BUNDLE := /home/zhouhaiy/tool_chain/oneapi/beta04/inteloneapi
INTEL_SYCL_BUNDLE_SYCL_INCLUDE := /tmp/

OPENCL_ROOT := /opt/intel/opencl

SYCL_LIB := mkl_sycl

CXX := g++

CXXFLAGS := -I $(INTEL_SYCL_BUNDLE_SYCL_INCLUDE) -I $(OPENCL_ROOT)/include -I ${INTEL_SYCL_BUNDLE}/mkl/latest/include

LDFLAGS := -L$(INTEL_SYCL_BUNDLE)/dpcpp/lib -lsycl -fPIC  -L$(OPENCL_ROOT) -lOpenCL -L${INTEL_SYCL_BUNDLE}/mkl/latest/lib/intel64_lin -lmkl_sycl -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm

all: gemm

gemm.o: gemm.cpp
	$(CXX) -std=c++11 -c -fPIC gemm.cpp $(CXXFLAGS)

gemm : gemm.o
	$(CXX) gemm.o  -o gemm $(LDFLAGS)

clean:
	rm -f gemm.o gemm

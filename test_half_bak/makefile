
COMPUTE_CPP_ROOT := /home/zhouhaiy/tool_chain/computecpp

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(COMPUTE_CPP_ROOT)/bin/compute++ 


COMPUTECPP_DEVICE_COMPILER_FLAGS := -O2 -mllvm -inline-threshold=1000 -sycl -intelspirmetadata -sycl-target spir64 -std=c++11  -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include

CXXFLAGS := -I $(COMPUTE_CPP_ROOT)/include -I $(OPENCL_ROOT)/include

LDFLAGS := -L$(COMPUTE_CPP_ROOT)/lib -lComputeCpp -L$(OPENCL_ROOT) -lOpenCL

all: test_half

test_half.sycl: test_half.cpp
	${SYCLCXX} ${COMPUTECPP_DEVICE_COMPILER_FLAGS} -c test_half.cpp

test_half.o: test_half.sycl test_half.cpp
	$(SYCLCXX) -std=c++11 -c -fPIC test_half.cpp -include test_half.sycl $(CXXFLAGS)

test_half.exe : test_half.o
	$(SYCLCXX) test_half.o  -o test_half.exe $(LDFLAGS)

clean:
	rm -f test_half.sycl test_half.exe test_half.o *.bc

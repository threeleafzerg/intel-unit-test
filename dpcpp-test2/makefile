
DPC_CPP_ROOT := /home/sunbear/intel/data_parallel_cpp_1.0_pre_alpha_update_7_011/dpcpp

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

#OLDCXX := g++

LDFLAGS := -L$(OPENCL_ROOT) -lOpenCL -L${DPC_CPP_ROOT}/lib -fsycl 

all: test

a.o: a.cpp
	$(SYCLCXX) ${DPCCPP_DEVICE_COMPILER_FLAGS} -fsycl -c a.cpp

test : a.o
	#$(SYCLCXX) -fsycl a.o -o test -L$(OPENCL_ROOT) -lOpenCL
	$(SYCLCXX) ${LDFLAGS} a.o -o test 

clean:
	rm -f test a.o

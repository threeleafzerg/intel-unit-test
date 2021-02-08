
DPC_CPP_ROOT := /home/sunbear/intel/dpcpp_bundle_1.0_prealpha_u8_020/dpcpp_compiler

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

LDFLAGS := -shared -L$(OPENCL_ROOT) -lOpenCL -L${DPC_CPP_ROOT}/lib -lsycl 

DPCCPP_DEVICE_COMPILER_FLAGS := -I ${DPC_CPP_ROOT}/include 

all: liba.so

a.o: a.cpp
	$(SYCLCXX) ${DPCCPP_DEVICE_COMPILER_FLAGS} -fsycl -fPIC -c a.cpp

liba.so : a.o 
	$(SYCLCXX) a.o -o liba.so $(LDFLAGS)

clean:
	rm -f liba.so a.o  

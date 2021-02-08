

DPC_CPP_ROOT := /home/zhouhaiy/tool_chain/compiler-nightly-build/compiler-nightly-0303/compiler/linux

OPENCL_ROOT := /opt/intel/opencl

SYCLCXX := $(DPC_CPP_ROOT)/bin/clang++

CXXFLAGS := -I $(DPC_CPP_ROOT)/lib/clang/11.0.0/include -I $(OPENCL_ROOT)/include -fsycl

LDFLAGS := -L $(OPENCL_ROOT)/lib -L $(DPC_CPP_ROOT)/lib  -lOpenCL -fsycl

all: first.exe

first.o: first.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c first.cpp

helper.o: helper.cpp
	$(SYCLCXX) -std=c++11 -c -fPIC helper.cpp

first.exe : first.o helper.o
	$(SYCLCXX) first.o helper.o -o first.exe $(LDFLAGS)

clean:
	rm -f first.exe first.o

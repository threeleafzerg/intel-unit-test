ONE_API_ROOT := /home/zhouhaiy/tool_chain/oneapi/beta04/inteloneapi

SYCL_ROOT := ${ONE_API_ROOT}/compiler/latest/linux

SYCLCXX := $(SYCL_ROOT)/bin/clang++

CXXFLAGS := -I $(SYCL_ROOT)/lib/clang/10.0.0/include -fsycl -g -O0

LDFLAGS := -L $(SYCL_ROOT)/lib -lOpenCL -fsycl -g

all: first.exe

first.o: first.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c first.cpp

first.exe : first.o
	$(SYCLCXX) first.o  -o first.exe $(LDFLAGS)

clean:
	rm -f first.exe first.o

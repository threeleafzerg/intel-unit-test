ONE_API_ROOT := /home/zhouhaiy/tool_chain/oneapi/beta01/inteloneapi

SYCL_ROOT := ${ONE_API_ROOT}/compiler/latest/linux

SYCLCXX := $(SYCL_ROOT)/bin/clang++

CXXFLAGS := -I $(SYCL_ROOT)/lib/clang/10.0.0/include -fsycl -fPIC

LDFLAGS := -shared -L $(SYCL_ROOT)/lib -lOpenCL -fsycl -fPIC

all: liba.so

a.o: a.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c a.cpp

liba.so : a.o
	$(SYCLCXX) a.o  -o liba.so $(LDFLAGS)

clean:
	rm -f liba.so a.o

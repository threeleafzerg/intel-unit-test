
SYCL_ROOT := /home/zhouhaiy/tool_chain/fix_mem_leak

SYCLCXX := $(SYCL_ROOT)/bin/clang++

CXXFLAGS := -I $(SYCL_ROOT)/lib/clang/10.0.0/include -fsycl
#CXXFLAGS := -I $(SYCL_ROOT)/lib/clang/10.0.0/include -g -O0

LDFLAGS := -L $(SYCL_ROOT)/lib -fsycl -lOpenCL 
#LDFLAGS := -L $(SYCL_ROOT)/lib -lsycl -lOpenCL -g

all: first.exe

first.o: first.cpp
	$(SYCLCXX) -std=c++14 $(CXXFLAGS) -c first.cpp

first.exe : first.o
	$(SYCLCXX) first.o  -o first.exe $(LDFLAGS)

clean:
	rm -f first.exe first.o

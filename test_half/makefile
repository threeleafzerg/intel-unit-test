
SYCL_ROOT := /home/zhouhaiy/tool_chain/dpcpp_build

SYCLCXX := $(SYCL_ROOT)/bin/clang++

CXXFLAGS := -I $(SYCL_ROOT)/lib/clang/10.0.0/include -fsycl -fsycl-targets=spir64_gen-unknown-linux-sycldevice
#CXXFLAGS := -I $(SYCL_ROOT)/lib/clang/10.0.0/include -g -O0

LDFLAGS := -L $(SYCL_ROOT)/lib -fsycl -lOpenCL 
#LDFLAGS := -L $(SYCL_ROOT)/lib -lsycl -lOpenCL -g

all: test_half

test_half.o: test_half.cpp
	$(SYCLCXX) -std=c++11 $(CXXFLAGS) -c test_half.cpp

test_half : test_half.o
	$(SYCLCXX) test_half.o  -o test_half $(LDFLAGS)

clean:
	rm -f test_half test_half.o

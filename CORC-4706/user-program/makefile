CXX := g++

ONE_API_ROOT := /home/zhouhaiy/tool_chain/oneapi/beta01/inteloneapi

SYCL_ROOT := ${ONE_API_ROOT}/compiler/latest/linux

CXXFLAGS := -I ./ -I $(SYCL_ROOT)/lib/clang/10.0.0/include-new

LDFLAGS := -L./ -la -L${SYCL_ROOT}/lib -lsycl

all: test

main.o: main.cpp
	$(CXX) -std=c++11 ${CXXFLAGS} -c main.cpp

test: main.o
	$(CXX) main.o -o test ${LDFLAGS}

clean:
	rm -f main.o test



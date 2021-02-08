
DPC_CPP_ROOT := /home/sunbear/intel/dpcpp_bundle_1.0_prealpha_u8_020/dpcpp_compiler

CXX := ${DPC_CPP_ROOT}/bin/clang++
#CXX := g++

CXXFLAGS := -I ./ -I ${DPC_CPP_ROOT}/include -fsycl
#CXXFLAGS := -I ./ -I ${DPC_CPP_ROOT}/include

LDFLAGS := -L./ -la -fsycl
#LDFLAGS := -L./ -la -L${DPC_CPP_ROOT}/lib -lsycl -L${DPC_CPP_ROOT}/lib -lOpenCL

all: test

main.o: main.cpp
	$(CXX) -std=c++11 ${CXXFLAGS} -c main.cpp

test : main.o
	$(CXX) main.o -o test ${LDFLAGS}

clean:
	rm -f main.o test



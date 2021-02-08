CXX := g++
SYCL_ROOT := /home/zhouhaiy/workspace/llvm/latest2/build
SYCL_CXX := $(SYCL_ROOT)/bin/clang++
LIB_CXXFLAGS := -I $(SYCL_ROOT)/include/sycl -fsycl -fPIC
EXE_CXXFLAGS := -I ./ -I $(SYCL_ROOT)/include/sycl
LIB_LDFLAGS := -shared -L $(SYCL_ROOT)/lib -lOpenCL -fsycl -fPIC
EXE_LDFLAGS := -L./ -luser -L${SYCL_ROOT}/lib -lsycl

all: test

libmain.o : libmain.cpp
	$(SYCL_CXX) -std=c++11 $(LIB_CXXFLAGS) -c libmain.cpp

libuser.so : libmain.o
	$(SYCL_CXX) libmain.o -o libuser.so $(LIB_LDFLAGS)

main.o: main.cpp
	$(CXX) -std=c++11 ${EXE_CXXFLAGS} -c main.cpp

test: main.o libuser.so
	$(CXX) main.o -o test ${EXE_LDFLAGS}

clean:
	rm -f main.o test libmain.o libuser.so



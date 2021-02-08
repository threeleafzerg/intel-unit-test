#!/bin/bash

export PATH=/home/zhouhaiy/tool_chain/fix_mem_leak/bin:${PATH}
clang++ -fsycl a.cpp b.cpp -c -fPIC
g++ main.cpp -c -fPIC
clang++ -fPIC -fsycl -fsycl-link a.o b.o -o dev.o
ar -rcs libuser.a  a.o b.o dev.o 
g++ main.o libuser.a  -L/home/zhouhaiy/tool_chain/fix_mem_leak/lib -lOpenCL -lsycl 
#g++ main.o a.o b.o dev.o -L/home/zhouhaiy/tool_chain/fix_mem_leak/lib -lOpenCL -lsycl

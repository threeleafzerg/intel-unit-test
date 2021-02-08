#!/bin/bash

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/sunbear/intel/data_parallel_cpp_1.0_pre_alpha_update_7_011/dpcpp/lib
make -j4 2>&1 > build.log

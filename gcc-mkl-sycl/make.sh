#!/bin/bash

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/zhouhaiy/tool_chain/oneapi/beta04/inteloneapi/compiler/latest/linux/lib
make -j4

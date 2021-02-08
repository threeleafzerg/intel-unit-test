#!/bin/bash

rm -f sycl_.txt
spirv-dis sycl_.spv -o sycl_.txt

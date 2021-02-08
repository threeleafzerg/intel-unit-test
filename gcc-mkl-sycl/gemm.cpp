/*******************************************************************************
* Copyright 2018-2019 Intel Corporation.
*
* This software and the related documents are Intel copyrighted  materials,  and
* your use of  them is  governed by the  express license  under which  they were
* provided to you (License).  Unless the License provides otherwise, you may not
* use, modify, copy, publish, distribute,  disclose or transmit this software or
* the related documents without Intel's prior written permission.
*
* This software and the related documents  are provided as  is,  with no express
* or implied  warranties,  other  than those  that are  expressly stated  in the
* License.
*******************************************************************************/

/*
*
*  Content:
*            mkl::{d,s,z,c}gemm example program text (SYCL interface)
*
*******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <limits>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>

#include <CL/sycl.hpp>
#include "mkl_blas_sycl.hpp"
//#include "mkl.h"
#include "mkl_blas_sycl_templates.hpp"
#include "mkl_blas_templates.hpp"
#include "test_common.hpp"
#include "mkl_allocator.hpp"

#define MAX_STR 128

#define FP float

using namespace cl::sycl;
using std::vector;

template <typename fp>
bool test(const device &dev, mkl::transpose transa, mkl::transpose transb, int m, int n, int k, int lda, int ldb, int ldc, fp alpha, fp beta)
{
    // mkl_allocator<fp,64> uses mkl_malloc/free to allocate data that is aligned on a 64-byte (cache line) boundary.
    double time_gemm;
    int i, nb_it = 10;

    vector<fp, mkl_allocator<fp, 64>> A, B, C, C_ref;

    // Prepare data.
    rand_matrix(A, transa, m, k, lda);
    rand_matrix(B, transb, k, n, ldb);
    rand_matrix(C, mkl::transpose::nontrans, m, n, ldc);
    C_ref = C;

    // Call standard MKL GEMM.
    MKL_INT m_mkl_int = m, n_mkl_int = n, k_mkl_int = k;
    MKL_INT lda_mkl_int = lda, ldb_mkl_int = ldb, ldc_mkl_int = ldc;

    using fp_mkl = typename mkl_type_info<fp>::type;

    ::gemm(mkl::fortran_char(transa), mkl::fortran_char(transb), &m_mkl_int, &n_mkl_int, &k_mkl_int, (fp_mkl*) &alpha, (fp_mkl*) A.data(), &lda_mkl_int, (fp_mkl*) B.data(), &ldb_mkl_int, (fp_mkl*) &beta, (fp_mkl*) C_ref.data(), &ldc_mkl_int);

    // Call SYCL GEMM.
    queue main_queue(dev);

    buffer<fp, 1> A_buffer(A.data(), range<1>(A.size()));
    buffer<fp, 1> B_buffer(B.data(), range<1>(B.size()));
    buffer<fp, 1> C_buffer(C.data(), range<1>(C.size()));

    try {
        mkl::gemm(main_queue, transa, transb, m, n, k, alpha, A_buffer, lda, B_buffer, ldb, beta, C_buffer, ldc);
    }
    catch(exception const& e) {
        std::cout << "SYCL exception during GEMM\n"
                  << e.what() << std::endl << "OpenCl status: " << e.get_cl_code() << std::endl;
    }

    // Check that the results match.
    auto C_accessor = C_buffer.template get_access<access::mode::read>();
    bool good = check_equal_matrix(C_accessor, C_ref, m, n, ldc, 10*k, std::cout);

    if (good) {
        time_gemm = dsecnd();
        for (i = 0; i < nb_it; i++) {
            mkl::gemm(main_queue, transa, transb, m, n, k, alpha, A_buffer,
                      lda, B_buffer, ldb, beta, C_buffer, ldc);
            main_queue.wait_and_throw();
        }
        time_gemm = dsecnd() - time_gemm;
        
        time_gemm = 1000. * time_gemm / (double) nb_it;

        std::cout << "GEMM parameters:\n";
        std::cout << "\ttransa = " << (int) transa << ", transb = " << (int) transb << std::endl;
        std::cout << "\tm = " << m << ", n = " << n << ", k = " << k << std::endl;
        std::cout << "\tlda = " << lda << ", ldb = " << ldb << ", ldc = " << ldc << std::endl;
        std::cout << "\talpha = " << alpha << ", beta = " << beta << std::endl;
        std::cout << "\tRunning time = " << time_gemm << " ms\n";
        std::cout << "Test was successful.\n";
    }
    else
        std::cout << "Result mismatch.\n";

    return good;
}

int main(int argc, char **argv)
{
    char mkl_version[MAX_STR];
    mkl_get_version_string(mkl_version, MAX_STR);

    std::cout << "Using " << mkl_version << std::endl;

    device host, cpu, gpu;
    bool hasCPU = true, hasGPU = true;

#ifdef USE_COMPLEX
    FP alpha = FP(2.0, -0.5);
    FP beta = FP(3.0, -1.5); 
#else
    FP alpha = FP(2.0), beta = FP(3.0);
#endif
  
    host = device(host_selector());     // Not necessary: cl::sycl::device defaults to host device.

    try {
        cpu = device(cpu_selector());
    } catch (...) {
        hasCPU = false;
    }

    try {
        gpu = device(gpu_selector());
    } catch (...) {
        hasGPU = false;
    }

    // FP defines the precision to use (float, std::complex<double>, etc.) and should be specified when compiling this file.
    std::cout << "Running GEMM test on host.\n";
    if (!test<FP>(host, mkl::transpose::trans, mkl::transpose::nontrans, 72, 27, 98, 101, 102, 103, alpha, beta))
        return 1;

    if (hasCPU) {
        std::cout << "Running GEMM test on CPU.\n";
        if (!test<FP>(cpu, mkl::transpose::trans, mkl::transpose::nontrans, 2, 3, 4, 5, 6, 7, alpha, beta))
            return 1;
    } else
        std::cout << "No CPU devices found; skipping CPU test.\n";
    
    if (hasGPU) {
        std::cout << "Running GEMM test on GPU.\n";
        if (!test<FP>(gpu, mkl::transpose::nontrans, mkl::transpose::nontrans, 79, 83, 91, 103, 105, 106, alpha, beta))
            return 1;
        if (!test<FP>(gpu, mkl::transpose::nontrans, mkl::transpose::trans, 79, 83, 91, 103, 105, 106, alpha, beta))
            return 1;
        if (!test<FP>(gpu, mkl::transpose::trans, mkl::transpose::nontrans, 79, 83, 91, 103, 105, 106, alpha, beta))
            return 1;
        if (!test<FP>(gpu, mkl::transpose::trans, mkl::transpose::trans, 79, 83, 91, 103, 105, 106, alpha, beta))
            return 1;
#ifdef USE_COMPLEX
        if (!test<FP>(gpu, mkl::transpose::trans, mkl::transpose::conjtrans, 79, 83, 91, 103, 105, 106, alpha, beta))
            return 1;
        if (!test<FP>(gpu, mkl::transpose::nontrans, mkl::transpose::conjtrans, 79, 83, 91, 103, 105, 106, alpha, beta))
            return 1;
#endif
    } else
        std::cout << "No GPU devices found; skipping GPU test.\n";

#ifdef FAIL_ON_MISSING_DEVICES
    if ( !hasCPU || !hasGPU ) return 1;
#endif

    return 0;
}

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

#ifndef _MKL_BLAS_SYCL_TEMPLATES_HPP__
#define _MKL_BLAS_SYCL_TEMPLATES_HPP__

#include "mkl_blas_sycl.hpp"

namespace mkl {

    // Level 3

    template <typename fp>
    void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
              int64_t k, fp alpha, cl::sycl::buffer<fp, 1> &a, int64_t lda,
              cl::sycl::buffer<fp, 1> &b, int64_t ldb, fp beta, cl::sycl::buffer<fp, 1> &c,
              int64_t ldc);

    template <>
    void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
              int64_t k, float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
              cl::sycl::buffer<float, 1> &b, int64_t ldb, float beta, cl::sycl::buffer<float, 1> &c,
              int64_t ldc)
    {
        sgemm(queue, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
              int64_t k, double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
              cl::sycl::buffer<double, 1> &b, int64_t ldb, double beta, cl::sycl::buffer<double, 1> &c,
              int64_t ldc)
    {
        dgemm(queue, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
              int64_t k, std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb,
              std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc)
    {
        cgemm(queue, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
              int64_t k, std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb,
              std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc)
    {
        zgemm(queue, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <typename fp>
    void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              fp alpha, cl::sycl::buffer<fp, 1> &a, int64_t lda,
              cl::sycl::buffer<fp, 1> &b, int64_t ldb, fp beta, cl::sycl::buffer<fp, 1> &c,
              int64_t ldc);

    template <>
    void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
              cl::sycl::buffer<float, 1> &b, int64_t ldb, float beta, cl::sycl::buffer<float, 1> &c,
              int64_t ldc)
    {
        ssymm(queue, left_right, upper_lower, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
              cl::sycl::buffer<double, 1> &b, int64_t ldb, double beta, cl::sycl::buffer<double, 1> &c,
              int64_t ldc)
    {
        dsymm(queue, left_right, upper_lower, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb,
              std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c,
              int64_t ldc)
    {
        csymm(queue, left_right, upper_lower, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb,
              std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c,
              int64_t ldc)
    {
        zsymm(queue, left_right, upper_lower, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <typename fp>
    void hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              std::complex<fp> alpha, cl::sycl::buffer<std::complex<fp>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<fp>, 1> &b, int64_t ldb,
              std::complex<fp> beta, cl::sycl::buffer<std::complex<fp>, 1> &c,
              int64_t ldc);

    template <>
    void hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb,
              std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c,
              int64_t ldc)
    {
        chemm(queue, left_right, upper_lower, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
              std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb,
              std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c,
              int64_t ldc)
    {
        zhemm(queue, left_right, upper_lower, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <typename fp>
    void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              fp alpha, cl::sycl::buffer<fp, 1> &a, int64_t lda,
              fp beta, cl::sycl::buffer<fp, 1> &c, int64_t ldc);

    template <>
    void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
              float beta, cl::sycl::buffer<float, 1> &c, int64_t ldc)
    {
        ssyrk(queue, upper_lower, trans, n, k, alpha, a, lda, beta, c, ldc);
    }

    template <>
    void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
              double beta, cl::sycl::buffer<double, 1> &c, int64_t ldc)
    {
        dsyrk(queue, upper_lower, trans, n, k, alpha, a, lda, beta, c, ldc);
    }

    template <>
    void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc)
    {
        csyrk(queue, upper_lower, trans, n, k, alpha, a, lda, beta, c, ldc);
    }

    template <>
    void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc)
    {
        zsyrk(queue, upper_lower, trans, n, k, alpha, a, lda, beta, c, ldc);
    }

    template <typename fp>
    void herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              fp alpha, cl::sycl::buffer<std::complex<fp>, 1> &a, int64_t lda,
              fp beta, cl::sycl::buffer<std::complex<fp>, 1> &c, int64_t ldc);

    template <>
    void herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              float alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              float beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc)
    {
        cherk(queue, upper_lower, trans, n, k, alpha, a, lda, beta, c, ldc);
    }

    template <>
    void herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
              double alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              double beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc)
    {
        zherk(queue, upper_lower, trans, n, k, alpha, a, lda, beta, c, ldc);
    }

    template <typename fp>
    void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               fp alpha, cl::sycl::buffer<fp, 1> &a, int64_t lda,
               cl::sycl::buffer<fp, 1> &b, int64_t ldb,
               fp beta, cl::sycl::buffer<fp, 1> &c, int64_t ldc);

    template <>
    void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
               cl::sycl::buffer<float, 1> &b, int64_t ldb,
               float beta, cl::sycl::buffer<float, 1> &c, int64_t ldc)
    {
        ssyr2k(queue, upper_lower, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
               cl::sycl::buffer<double, 1> &b, int64_t ldb,
               double beta, cl::sycl::buffer<double, 1> &c, int64_t ldc)
    {
        dsyr2k(queue, upper_lower, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
               cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb,
               std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc)
    {
        csyr2k(queue, upper_lower, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
               cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb,
               std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc)
    {
        zsyr2k(queue, upper_lower, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <typename fp>
    void her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               std::complex<fp> alpha, cl::sycl::buffer<std::complex<fp>, 1> &a, int64_t lda,
               cl::sycl::buffer<std::complex<fp>, 1> &b, int64_t ldb,
               fp beta, cl::sycl::buffer<std::complex<fp>, 1> &c, int64_t ldc);

    template <>
    void her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
               cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb,
               float beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc)
    {
        cher2k(queue, upper_lower, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <>
    void her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
               std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
               cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb,
               double beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc)
    {
        zher2k(queue, upper_lower, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }

    template <typename fp>
    void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              fp alpha, cl::sycl::buffer<fp, 1> &a, int64_t lda,
              cl::sycl::buffer<fp, 1> &b, int64_t ldb);

    template <>
    void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
              cl::sycl::buffer<float, 1> &b, int64_t ldb)
    {
        strmm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

    template <>
    void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
              cl::sycl::buffer<double, 1> &b, int64_t ldb)
    {
        dtrmm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

     template <>
    void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb)
    {
        ctrmm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

    template <>
    void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb)
    {
        ztrmm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

    template <typename fp>
    void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              fp alpha, cl::sycl::buffer<fp, 1> &a, int64_t lda,
              cl::sycl::buffer<fp, 1> &b, int64_t ldb);

    template <>
    void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
              cl::sycl::buffer<float, 1> &b, int64_t ldb)
    {
        strsm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

    template <>
    void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
              cl::sycl::buffer<double, 1> &b, int64_t ldb)
    {
        dtrsm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

     template <>
    void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb)
    {
        ctrsm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

    template <>
    void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose trans, diag unit_diag,
              int64_t m, int64_t n,
              std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb)
    {
        ztrsm(queue, left_right, upper_lower, trans, unit_diag, m, n, alpha, a, lda, b, ldb);
    }

    // Level 2

    template <typename fp>
    void gemv(cl::sycl::queue &queue, transpose trans, int64_t m, int64_t n, fp alpha,
              cl::sycl::buffer<fp,1> &a, int64_t lda,
              cl::sycl::buffer<fp,1> &x, int64_t incx, fp beta,
              cl::sycl::buffer<fp,1> &y, int64_t incy);

    template <>
    void gemv(cl::sycl::queue &queue, transpose trans, int64_t m, int64_t n, float alpha,
              cl::sycl::buffer<float,1> &a, int64_t lda,
              cl::sycl::buffer<float,1> &x, int64_t incx, float beta,
              cl::sycl::buffer<float,1> &y, int64_t incy)
    {
        sgemv(queue, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
    }

    template <>
    void gemv(cl::sycl::queue &queue, transpose trans, int64_t m, int64_t n, double alpha,
              cl::sycl::buffer<double,1> &a, int64_t lda,
              cl::sycl::buffer<double,1> &x, int64_t incx, double beta,
              cl::sycl::buffer<double,1> &y, int64_t incy)
    {
        dgemv(queue, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
    }

    template <>
    void gemv(cl::sycl::queue &queue, transpose trans, int64_t m, int64_t n, std::complex<float> alpha,
              cl::sycl::buffer<std::complex<float>,1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<float>,1> &x, int64_t incx, std::complex<float> beta,
              cl::sycl::buffer<std::complex<float>,1> &y, int64_t incy)
    {
        cgemv(queue, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
    }

    template <>
    void gemv(cl::sycl::queue &queue, transpose trans, int64_t m, int64_t n, std::complex<double> alpha,
              cl::sycl::buffer<std::complex<double>,1> &a, int64_t lda,
              cl::sycl::buffer<std::complex<double>,1> &x, int64_t incx, std::complex<double> beta,
              cl::sycl::buffer<std::complex<double>,1> &y, int64_t incy)
    {
        zgemv(queue, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
    }

    // Level 1

    template <typename fp>
    void dotc(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<fp,1> &x,
              int64_t incx, cl::sycl::buffer<fp,1> &y, int64_t incy,
              cl::sycl::buffer<fp,1> &result);

    template <>
    void dotc(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>,1> &x,
              int64_t incx, cl::sycl::buffer<std::complex<float>,1> &y, int64_t incy,
              cl::sycl::buffer<std::complex<float>,1> &result)
    {
        cdotc(queue, n, x, incx, y, incy, result);
    }

    template <>
    void dotc(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>,1> &x,
              int64_t incx, cl::sycl::buffer<std::complex<double>,1> &y, int64_t incy,
              cl::sycl::buffer<std::complex<double>,1> &result)
    {
        zdotc(queue, n, x, incx, y, incy, result);
    }



    template <typename fp>
    void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<fp, 1> &x, int64_t incx,
               cl::sycl::buffer<int64_t, 1> &result);

    template <>
    void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
               cl::sycl::buffer<int64_t, 1> &result)
    {
        isamax(queue, n, x, incx, result);
    }

    template <>
    void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
               cl::sycl::buffer<int64_t, 1> &result)
    {
        idamax(queue, n, x, incx, result);
    }

    template <>
    void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x, int64_t incx,
               cl::sycl::buffer<int64_t, 1> &result)
    {
        icamax(queue, n, x, incx, result);
    }

    template <>
    void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x, int64_t incx,
               cl::sycl::buffer<int64_t, 1> &result)
    {
        izamax(queue, n, x, incx, result);
    }
}

#endif /* header guard */

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

#ifndef _MKL_BLAS_TEMPLATES_HPP__
#define _MKL_BLAS_TEMPLATES_HPP__

#include "mkl_blas.h"

// Level 3

template <typename fp>
void gemm(const char *transa, const char *transb, const MKL_INT *m, const MKL_INT *n, const MKL_INT *k,
          const fp *alpha, const fp *a, const MKL_INT *lda, const fp *b, const MKL_INT *ldb,
          const fp *beta, fp *c, const MKL_INT *ldc);

template <>
void gemm(const char *transa, const char *transb, const MKL_INT *m, const MKL_INT *n, const MKL_INT *k,
          const float *alpha, const float *a, const MKL_INT *lda, const float *b, const MKL_INT *ldb,
          const float *beta, float *c, const MKL_INT *ldc)
{
    return sgemm(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void gemm(const char *transa, const char *transb, const MKL_INT *m, const MKL_INT *n, const MKL_INT *k,
          const double *alpha, const double *a, const MKL_INT *lda, const double *b, const MKL_INT *ldb,
          const double *beta, double *c, const MKL_INT *ldc)
{
    return dgemm(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void gemm(const char *transa, const char *transb, const MKL_INT *m, const MKL_INT *n, const MKL_INT *k,
          const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          const MKL_Complex8 *b, const MKL_INT *ldb,
          const MKL_Complex8 *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return cgemm(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void gemm(const char *transa, const char *transb, const MKL_INT *m, const MKL_INT *n, const MKL_INT *k,
          const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          const MKL_Complex16 *b, const MKL_INT *ldb,
          const MKL_Complex16 *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zgemm(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}


template <typename fp>
void symm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const fp *alpha, const fp *a, const MKL_INT *lda, const fp *b, const MKL_INT *ldb,
          const fp *beta, fp *c, const MKL_INT *ldc);

template <>
void symm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const float *alpha, const float *a, const MKL_INT *lda, const float *b, const MKL_INT *ldb,
          const float *beta, float *c, const MKL_INT *ldc)
{
    return ssymm(left_right, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void symm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const double *alpha, const double *a, const MKL_INT *lda, const double *b, const MKL_INT *ldb,
          const double *beta, double *c, const MKL_INT *ldc)
{
    return dsymm(left_right, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void symm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          const MKL_Complex8 *b, const MKL_INT *ldb,
          const MKL_Complex8 *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return csymm(left_right, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void symm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          const MKL_Complex16 *b, const MKL_INT *ldb,
          const MKL_Complex16 *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zsymm(left_right, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}


template <typename fp>
void hemm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const fp *alpha, const fp *a, const MKL_INT *lda, const fp *b, const MKL_INT *ldb,
          const fp *beta, fp *c, const MKL_INT *ldc);

template <>
void hemm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          const MKL_Complex8 *b, const MKL_INT *ldb,
          const MKL_Complex8 *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return chemm(left_right, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void hemm(const char *left_right, const char *uplo, const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          const MKL_Complex16 *b, const MKL_INT *ldb,
          const MKL_Complex16 *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zhemm(left_right, uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <typename fp>
void syrk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const fp *alpha, const fp *a, const MKL_INT *lda,
          const fp *beta, fp *c, const MKL_INT *ldc);

template <>
void syrk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const float *alpha, const float *a, const MKL_INT *lda,
          const float *beta, float *c, const MKL_INT *ldc)
{
    return ssyrk(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

template <>
void syrk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const double *alpha, const double *a, const MKL_INT *lda,
          const double *beta, double *c, const MKL_INT *ldc)
{
    return dsyrk(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

template <>
void syrk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          const MKL_Complex8 *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return csyrk(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

template <>
void syrk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          const MKL_Complex16 *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zsyrk(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

template <typename fp_scalar, typename fp_data>
void herk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const fp_scalar *alpha, const fp_data *a, const MKL_INT *lda,
          const fp_scalar *beta, fp_data *c, const MKL_INT *ldc);

template <>
void herk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const float *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          const float *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return cherk(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

template <>
void herk(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
          const double *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          const double *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zherk(uplo, trans, n, k, alpha, a, lda, beta, c, ldc);
}

template <typename fp>
void syr2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const fp *alpha, const fp *a, const MKL_INT *lda,
           const fp *b, const MKL_INT *ldb,
           const fp *beta, fp *c, const MKL_INT *ldc);

template <>
void syr2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const float *alpha, const float *a, const MKL_INT *lda,
           const float *b, const MKL_INT *ldb,
           const float *beta, float *c, const MKL_INT *ldc)
{
    return ssyr2k(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void syr2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const double *alpha, const double *a, const MKL_INT *lda,
           const double *b, const MKL_INT *ldb,
           const double *beta, double *c, const MKL_INT *ldc)
{
    return dsyr2k(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void syr2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
           const MKL_Complex8 *b, const MKL_INT *ldb,
           const MKL_Complex8 *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return csyr2k(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void syr2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
           const MKL_Complex16 *b, const MKL_INT *ldb,
           const MKL_Complex16 *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zsyr2k(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <typename fp_scalar, typename fp_data>
void her2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const fp_data *alpha, const fp_data *a, const MKL_INT *lda,
           const fp_data *b, const MKL_INT *ldb,
           const fp_scalar *beta, fp_data *c, const MKL_INT *ldc);

template <>
void her2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
           const MKL_Complex8 *b, const MKL_INT *ldb,
           const float *beta, MKL_Complex8 *c, const MKL_INT *ldc)
{
    return cher2k(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}

template <>
void her2k(const char *uplo, const char *trans, const MKL_INT *n, const MKL_INT *k,
           const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
           const MKL_Complex16 *b, const MKL_INT *ldb,
           const double *beta, MKL_Complex16 *c, const MKL_INT *ldc)
{
    return zher2k(uplo, trans, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}


template <typename fp>
void trmm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const fp *alpha, const fp *a, const MKL_INT *lda,
          fp *b, const MKL_INT *ldb);

template <>
void trmm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const float *alpha, const float *a, const MKL_INT *lda,
          float *b, const MKL_INT *ldb)
{
    strmm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <>
void trmm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const double *alpha, const double *a, const MKL_INT *lda,
          double *b, const MKL_INT *ldb)
{
    dtrmm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <>
void trmm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          MKL_Complex8 *b, const MKL_INT *ldb)
{
    ctrmm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <>
void trmm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          MKL_Complex16 *b, const MKL_INT *ldb)
{
    ztrmm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <typename fp>
void trsm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const fp *alpha, const fp *a, const MKL_INT *lda,
          fp *b, const MKL_INT *ldb);

template <>
void trsm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const float *alpha, const float *a, const MKL_INT *lda,
          float *b, const MKL_INT *ldb)
{
    strsm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <>
void trsm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const double *alpha, const double *a, const MKL_INT *lda,
          double *b, const MKL_INT *ldb)
{
    dtrsm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <>
void trsm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex8 *alpha, const MKL_Complex8 *a, const MKL_INT *lda,
          MKL_Complex8 *b, const MKL_INT *ldb)
{
    ctrsm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

template <>
void trsm(const char *side, const char *uplo, const char *transa, const char *diag,
          const MKL_INT *m, const MKL_INT *n,
          const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
          MKL_Complex16 *b, const MKL_INT *ldb)
{
    ztrsm(side, uplo, transa, diag, m, n, alpha, a, lda, b, ldb);
}

// Level 2

template <typename fp>
void gemv(const char *trans, const MKL_INT *m, const MKL_INT *n, const fp *alpha,
          const fp *a, const MKL_INT *lda, const fp *x, const MKL_INT *incx,
          const fp *beta, fp *y, const MKL_INT *incy);

template <>
void gemv(const char *trans, const MKL_INT *m, const MKL_INT *n, const float *alpha,
          const float *a, const MKL_INT *lda, const float *x, const MKL_INT *incx,
          const float *beta, float *y, const MKL_INT *incy)
{
    sgemv(trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
}

template <>
void gemv(const char *trans, const MKL_INT *m, const MKL_INT *n, const double *alpha,
          const double *a, const MKL_INT *lda, const double *x, const MKL_INT *incx,
          const double *beta, double *y, const MKL_INT *incy)
{
    dgemv(trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
}

template <>
void gemv(const char *trans, const MKL_INT *m, const MKL_INT *n, const MKL_Complex8 *alpha,
          const MKL_Complex8 *a, const MKL_INT *lda, const MKL_Complex8 *x, const MKL_INT *incx,
          const MKL_Complex8 *beta, MKL_Complex8 *y, const MKL_INT *incy)
{
    cgemv(trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
}

template <>
void gemv(const char *trans, const MKL_INT *m, const MKL_INT *n, const MKL_Complex16 *alpha,
          const MKL_Complex16 *a, const MKL_INT *lda, const MKL_Complex16 *x, const MKL_INT *incx,
          const MKL_Complex16 *beta, MKL_Complex16 *y, const MKL_INT *incy)
{
    zgemv(trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
}

// Level 1

template <typename fp>
void dotc(fp *pres, const MKL_INT *n, const fp *x, const MKL_INT *incx, const fp *y, const MKL_INT *incy);

template <>
void dotc(MKL_Complex8 *pres, const MKL_INT *n, const MKL_Complex8 *x, const MKL_INT *incx, const MKL_Complex8 *y, const MKL_INT *incy)
{
    cdotc(pres, n, x, incx, y, incy);
}

template <>
void dotc(MKL_Complex16 *pres, const MKL_INT *n, const MKL_Complex16 *x, const MKL_INT *incx, const MKL_Complex16 *y, const MKL_INT *incy)
{
    zdotc(pres, n, x, incx, y, incy);
}



template <typename fp>
MKL_INT iamax(const MKL_INT *n, const fp *x, const MKL_INT *incx);

template <>
MKL_INT iamax(const MKL_INT *n, const float *x, const MKL_INT *incx)
{
    return isamax(n, x, incx);
}

template <>
MKL_INT iamax(const MKL_INT *n, const double *x, const MKL_INT *incx)
{
    return idamax(n, x, incx);
}

template <>
MKL_INT iamax(const MKL_INT *n, const MKL_Complex8 *x, const MKL_INT *incx)
{
    return icamax(n, x, incx);
}

template <>
MKL_INT iamax(const MKL_INT *n, const MKL_Complex16 *x, const MKL_INT *incx)
{
    return izamax(n, x, incx);
}


#endif /* header guard */

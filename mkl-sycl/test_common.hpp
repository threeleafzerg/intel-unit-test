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

#ifndef _TEST_COMMON_HPP__
#define _TEST_COMMON_HPP__

#include <complex>
#include <CL/sycl.hpp>

// Complex helpers.
template <typename T>
struct complex_info {
    using real_type = T;
    static const bool is_complex = false;
};

template <typename T>
struct complex_info<std::complex<T>> {
    using real_type = T;
    static const bool is_complex = true;
};

template <typename T> constexpr bool is_complex()       { return complex_info<T>::is_complex; }
template <typename T> constexpr int num_components()    { return is_complex<T>() ? 2 : 1; }

// Matrix helpers.
template <typename T> constexpr T inner_dimension(mkl::transpose trans, T m, T n)     { return (trans == mkl::transpose::nontrans) ? m : n; }
template <typename T> constexpr T outer_dimension(mkl::transpose trans, T m, T n)     { return (trans == mkl::transpose::nontrans) ? n : m; }
template <typename T> constexpr T matrix_size(mkl::transpose trans, T m, T n, T ldm)  { return outer_dimension(trans, m, n) * ldm; }

// SYCL buffer creation helper.
//   Not currently working on GPU devices, due to compiler limitations. Instead,
//   call the constructor directly (i.e. inline this code by hand), as in:
//      cl::sycl::buffer buf(v.data(), cl::sycl::range<1>(v.size()));
template <typename vec> cl::sycl::buffer<typename vec::value_type,1> make_buffer(const vec &v) {
    cl::sycl::buffer<typename vec::value_type, 1> buf(v.data(), cl::sycl::range<1>(v.size()));
    return buf;
}

// MKL helpers.
template <typename T>
struct mkl_type_info {
    using type = T;
};

template <> struct mkl_type_info<std::complex<float>>           { using type = MKL_Complex8; };
template <> struct mkl_type_info<std::complex<double>>          { using type = MKL_Complex16; };

// Random initialization.
template <typename fp> fp rand_scalar()							{ return fp(std::rand()) / RAND_MAX - fp(0.5); }
template <typename fp> std::complex<fp> rand_complex_scalar()	{ return std::complex<fp>(rand_scalar<fp>(), rand_scalar<fp>()); }
template <> std::complex<float>  rand_scalar()					{ return rand_complex_scalar<float>(); }
template <> std::complex<double> rand_scalar()					{ return rand_complex_scalar<double>(); }

template <typename fp> fp rand_scalar(int mag)					{ fp tmp = fp(mag) + fp(std::rand()) / RAND_MAX - fp(0.5); if (std::rand() % 2) return tmp; else return -tmp; }
template <typename fp> std::complex<fp> rand_complex_scalar(int mag)	{ return std::complex<fp>(rand_scalar<fp>(mag), rand_scalar<fp>(mag)); }
template <> std::complex<float>  rand_scalar(int mag)			{ return rand_complex_scalar<float>(mag); }
template <> std::complex<double> rand_scalar(int mag)			{ return rand_complex_scalar<double>(mag); }

template <typename vec> void rand_vector(vec &v, int n, int inc)
{
    using fp = typename vec::value_type;
    int abs_inc = std::abs(inc);

    v.resize(n * abs_inc);

    for (int i = 0; i < n; i++)
        v[i*abs_inc] = rand_scalar<fp>();
}

template <typename vec> void rand_matrix(vec &M, mkl::transpose trans, int m, int n, int ld)
{
    using fp = typename vec::value_type;

    M.resize(matrix_size(trans, m, n, ld));

    if (trans == mkl::transpose::nontrans) {
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++)
                M[i + j * ld] = rand_scalar<fp>();
    } else {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[j + i * ld] = rand_scalar<fp>();
    }
}

template <typename vec> void rand_trsm_matrix(vec &M, mkl::transpose trans, int m, int n, int ld)
{
    using fp = typename vec::value_type;

    M.resize(matrix_size(trans, m, n, ld));

    if (trans == mkl::transpose::nontrans) {
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++) {
                if (i == j)
                    M[i + j * ld] = rand_scalar<fp>(10);
                else
                    M[i + j * ld] = rand_scalar<fp>();
            }
    } else {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (i == j)
                    M[j + i * ld] = rand_scalar<fp>(10);
                else
                    M[j + i * ld] = rand_scalar<fp>();
            }
    }
}

// Correctness checking.
template <typename fp> bool check_equal(fp x, fp x_ref, int error_mag)
{
    using fp_real = typename complex_info<fp>::real_type;
    fp_real bound = (error_mag * num_components<fp>() * std::numeric_limits<fp_real>::epsilon());
    bool ok;
    
    fp_real aerr = std::abs(x - x_ref);
    fp_real rerr = aerr/std::abs(x_ref);
    ok = (rerr <= bound) || (aerr <= bound);
    if (!ok) std::cout << "relative error = " << rerr << " absolute error = " << aerr << " limit = " << bound << std::endl;
    return ok;
}

template <typename fp> bool check_equal_trsm(fp x, fp x_ref, int error_mag)
{
    using fp_real = typename complex_info<fp>::real_type;
    fp_real bound = std::max(fp_real(5e-5), (error_mag * num_components<fp>() * std::numeric_limits<fp_real>::epsilon()));
    bool ok;
    
    fp_real aerr = std::abs(x - x_ref);
    fp_real rerr = aerr/std::abs(x_ref);
    ok = (rerr <= bound) || (aerr <= bound);
    if (!ok) std::cout << "relative error = " << rerr << " absolute error = " << aerr << " limit = " << bound << std::endl;
    return ok;
}

template <typename fp> bool check_equal(fp x, fp x_ref, int error_mag, std::ostream &out)
{
    bool good = check_equal(x, x_ref, error_mag);

    if (!good)
        out << "Difference in result: SYCL " << x << " vs. standard MKL " << x_ref;

    return good;
}

template <typename vec1, typename vec2> bool check_equal_vector(vec1 &v, vec2 &v_ref, int n, int inc, int error_mag, std::ostream &out)
{
    int abs_inc = std::abs(inc);
    bool good = true;
    
    for (int i = 0; i < n; i++) {
        if (!check_equal(v[i*abs_inc], v_ref[i*abs_inc], error_mag)) {
            int i_actual = (inc > 0) ? i : n-i;
            std::cout << "Difference in entry " << i_actual << ": SYCL " << v[i*abs_inc] << " vs. standard MKL " << v_ref[i*abs_inc] << std::endl;
            good = false;
        }
    }

    return good;
}

template <typename acc1, typename acc2> bool check_equal_matrix(acc1 &M, acc2 &M_ref, int m, int n, int ld, int error_mag, std::ostream &out)
{
    bool good = true;

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (!check_equal(M[i + j * ld], M_ref[i + j * ld], error_mag)) {
                out << "Difference in entry (" << i << ',' << j << "): SYCL " << M[i + j * ld] << " vs. standard MKL " << M_ref[i + j * ld] << std::endl;
                good = false;
            }
        }
    }

    return good;
}

template <typename acc1, typename acc2> bool check_equal_trsm_matrix(acc1 &M, acc2 &M_ref, int m, int n, int ld, int error_mag, std::ostream &out)
{
    bool good = true;

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (!check_equal_trsm(M[i + j * ld], M_ref[i + j * ld], error_mag)) {
                out << "Difference in entry (" << i << ',' << j << "): SYCL " << M[i + j * ld] << " vs. standard MKL " << M_ref[i + j * ld] << std::endl;
                good = false;
            }
        }
    }

    return good;
}


#endif /* header guard */

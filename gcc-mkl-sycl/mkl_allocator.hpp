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

#ifndef __MKL_ALLOCATOR_H
#define __MKL_ALLOCATOR_H

#include <cstddef>
#include <limits>
#include <type_traits>
#include "mkl.h"

template <typename T, int align>
struct mkl_allocator
{
    typedef T*			pointer;
    typedef const T*	const_pointer;
    typedef void*		void_pointer;
    typedef const void*	const_void_pointer;
    typedef T			value_type;
    typedef size_t		size_type;
    typedef ptrdiff_t	difference_type;

    template <typename U> struct rebind { typedef mkl_allocator<U,align> other; };

    mkl_allocator() noexcept {}
	template <typename U, int align2> mkl_allocator(mkl_allocator<U,align2> &other)  noexcept {}
    template <typename U, int align2> mkl_allocator(mkl_allocator<U,align2> &&other) noexcept {}

    T* allocate(size_t n) {
        void *mem = mkl_malloc(n * sizeof(T), align);
        if (!mem) throw std::bad_alloc();

        return static_cast<T*>(mem);
    }
	
	void deallocate(T *p, size_t n) noexcept {
		mkl_free(p);
	}

    constexpr size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

	template <typename U, int align2> constexpr bool operator==(const mkl_allocator<U,align2>) const noexcept { return true;  }
	template <typename U, int align2> constexpr bool operator!=(const mkl_allocator<U,align2>) const noexcept { return false; }

    typedef std::true_type is_always_equal;
};

#endif
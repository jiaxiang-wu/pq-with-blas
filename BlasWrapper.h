/*
  File Name: BlasWrapper.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 27 Jan 2016 08:35:44 PM CST
 */

#ifndef BLASWRAPPER_H_INCLUDED
#define BLASWRAPPER_H_INCLUDED

#include <mkl.h>

#include "Array.hpp"
#include "SprsArray.hpp"

/*
 * All matrices are in the row-major ordering, e.g. the element comes after
 *   a[0][0] is a[0][1] (C/C++ style), not a[1][0] (Fortran style).
 */

// INTRO
//   compute the product between a dense matrix and a dense vector
// INPUT
//   a: m x k
//   b: 1 x k
//   enblMKL: true (use MKL) / false (use built-in)
// OUTPUT
//   c: m x 1 (= a * b')
void MatVecProd(const Array<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c);

// INTRO
//   compute the product between two dense matrices
// INPUT
//   a: m x k
//   b: n x k
//   enblMKL: true (use MKL) / false (use built-in)
// OUTPUT
//   c: m x n (= a * b')
void MatMatProd(const Array<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c);

// INTRO
//   compute the product between a sparse matrix and a dense vector
// INPUT
//   a: m x k
//   b: k x 1
//   enblMKL: true (use MKL) / false (use built-in)
// OUTPUT
//   c: m x 1 (= a * b)
void SprsMatVecProd(const SprsArray<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c);

// INTRO
//   compute the product between a sparse matrix and a dense matrix
// INPUT
//   a: m x k
//   b: k x n
//   enblMKL: true (use MKL) / false (use built-in)
// OUTPUT
//   c: m x n (= a * b)
void SprsMatMatProd(const SprsArray<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c);

#endif // BLASWRAPPER_H_INCLUDED


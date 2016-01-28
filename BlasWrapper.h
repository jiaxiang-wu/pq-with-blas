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

/*
 * All matrices are in the column-major ordering, e.g. the element comes after
 *   a[0][0] is a[1][0], not a[0][1] (as in the convention for C/C++).
 */

// INTRO
//   compute the product between a vector and a matrix
// INPUT
//   a: k x 1
//   b: k x n
// OUTPUT
//   c: 1 x n (= trans(a) * b)
void VecMatProd(const Array<float>& a, const Array<float>& b, Array<float>& c);

// INTRO
//   compute the product between two matrices
// INPUT
//   a: k x m
//   b: k x n
// OUTPUT
//   c: m x n (= trans(a) * b)
void MatMatProd(const Array<float>& a, const Array<float>& b, Array<float>& c);

#endif // BLASWRAPPER_H_INCLUDED


/*
  File Name: BlasWrapper.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 01:56:47 PM CST
 */

#include "BlasWrapper.h"

#include <iostream>
#include <cstdlib>

inline float CalcInPdVal(const float* pa, const float* pb, const std::size_t len);

void MatVecProd(const Array<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c) {
  // obtain basic variables
  std::size_t m = a.GetDimLen(0);
  std::size_t k = a.GetDimLen(1);

  // verify the input/output arrays' size
  if ((b.GetDimLen(0) != 1) || (b.GetDimLen(1) != k)) {
    std::cout << "[ERROR] invalid input array(s)" << std::endl;
    exit(-1);
  } // ENDIF: b
  if ((c.GetDimLen(0) != m) || (c.GetDimLen(1) != 1)) {
    std::cout << "[ERROR] invalid output array" << std::endl;
    exit(-1);
  } // ENDIF: c

  // compute the product between a dense matrix and a dense vector
  if (enblMKL) {
    // use MKL implementation
    cblas_sgemv(CblasRowMajor, CblasNoTrans, m, k, 1.0, \
        a.GetDataPtr(), k, b.GetDataPtr(), 1, 0.0, c.GetDataPtr(), 1);
  } else {
    // use built-in implementaion
    const float* pb = b.GetDataPtr();
    float* pc = c.GetDataPtr();
    for (std::size_t im = 0; im < m; ++im) {
      const float* pa = a.GetDataPtr() + im * k;
      pc[im] = CalcInPdVal(pa, pb, k);
    } // ENDFOR: im
  } // ENDIF: enblMKL
}

void MatMatProd(const Array<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c) {
  // obtain basic variables
  std::size_t m = a.GetDimLen(0);
  std::size_t k = a.GetDimLen(1);
  std::size_t n = b.GetDimLen(0);

  // verify the input/output arrays' size
  if (b.GetDimLen(1) != k) {
    std::cout << "[ERROR] invalid input array(s)" << std::endl;
    exit(-1);
  } // ENDIF: b
  if ((c.GetDimLen(0) != m) || (c.GetDimLen(1) != n)) {
    std::cout << "[ERROR] invalid output array" << std::endl;
    exit(-1);
  } // ENDIF: c

  // compute the product between two dense matrices
  if (enblMKL) {
    // use MKL implementation
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k, 1.0, \
        a.GetDataPtr(), k, b.GetDataPtr(), k, 0.0, c.GetDataPtr(), n);
  } else {
    // use built-in implementaion
    for (std::size_t im = 0; im < m; ++im) {
      const float* pa = a.GetDataPtr() + im * k;
      float* pc = c.GetDataPtr() + im * n;
      for (std::size_t in = 0; in < n; ++in) {
        const float* pb = b.GetDataPtr() + in * k;
        pc[in] = CalcInPdVal(pa, pb, k);
      } // ENDFOR: in
    } // ENDFOR: im
  } // ENDIF: enblMKL
}

// TODO
void SprsMatVecProd(const SprsArray<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c) {
  /*
  // obtain basic variables
  std::size_t m = a.GetDimLen(0);
  std::size_t k = a.GetDimLen(1);

  // verify the input/output arrays' size
  if ((b.GetDimLen(0) != 1) || (b.GetDimLen(1) != k)) {
    std::cout << "[ERROR] invalid input array(s)" << std::endl;
    exit(-1);
  } // ENDIF: b
  if ((c.GetDimLen(0) != m) || (c.GetDimLen(1) != 1)) {
    std::cout << "[ERROR] invalid output array" << std::endl;
    exit(-1);
  } // ENDIF: c

  // compute the product between a dense matrix and a dense vector
  if (enblMKL) {
    // use MKL implementation
    cblas_sgemv(CblasRowMajor, CblasNoTrans, m, k, 1.0, \
        a.GetDataPtr(), k, b.GetDataPtr(), 1, 0.0, c.GetDataPtr(), 1);
  } else {
    // use built-in implementaion
    const float* pb = b.GetDataPtr();
    float* pc = c.GetDataPtr();
    for (std::size_t im = 0; im < m; ++im) {
      const float* pa = a.GetDataPtr() + im * k;
      pc[im] = CalcInPd(pa, pb, k);
    } // ENDFOR: im
  } // ENDIF: enblMKL
  */
}

// TODO
void SprsMatMatProd(const SprsArray<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c) {
  /*
  // obtain basic variables
  std::size_t m = a.GetDimLen(0);
  std::size_t k = a.GetDimLen(1);
  std::size_t n = b.GetDimLen(0);

  // verify the input/output arrays' size
  if (b.GetDimLen(1) != k) {
    std::cout << "[ERROR] invalid input array(s)" << std::endl;
    exit(-1);
  } // ENDIF: b
  if ((c.GetDimLen(0) != m) || (c.GetDimLen(1) != n)) {
    std::cout << "[ERROR] invalid output array" << std::endl;
    exit(-1);
  } // ENDIF: c

  // compute the product between two dense matrices
  if (enblMKL) {
    // use MKL implementation
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k, 1.0, \
        a.GetDataPtr(), k, b.GetDataPtr(), k, 0.0, c.GetDataPtr(), n);
  } else {
    // use built-in implementaion
    for (std::size_t im = 0; im < m; ++im) {
      const float* pa = a.GetDataPtr() + im * k;
      float* pc = c.GetDataPtr() + im * n;
      for (std::size_t in = 0; in < n; ++in) {
        const float* pb = b.GetDataPtr() + in * k;
        pc[in] = CalcInPd(pa, pb, k);
      } // ENDFOR: in
    } // ENDFOR: im
  } // ENDIF: enblMKL
  */
}

float CalcInPdVal(const float* pa, const float* pb, const std::size_t len) {
  float val = 0.0;
  for (std::size_t idx = 0; idx < len; ++idx) {
    val += pa[idx] * pb[idx];
  } // ENDFOR: idx
  return val;
}


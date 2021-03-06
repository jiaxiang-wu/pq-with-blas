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

void SprsMatVecProd(const SprsArray<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c) {
  // obtain basic variables
  std::size_t m = a.GetRowCnt();
  std::size_t k = a.GetColCnt();

  // verify the input/output arrays' size
  if ((b.GetDimLen(0) != k) || (b.GetDimLen(1) != 1)) {
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
    char transa = 'n';
    MKL_INT m_mkl = m;
    MKL_INT k_mkl = k;
    float alpha = 1.0;
    char matdescra[] = "G__C";
    float* val = a.GetVal();
    MKL_INT* idx = a.GetIdx();
    MKL_INT* ptrb = a.GetPtrb();
    MKL_INT* ptre = a.GetPtre();
    float* x = b.GetDataPtr();
    float beta = 0.0;
    float* y = c.GetDataPtr();
    mkl_scsrmv(&transa, &m_mkl, &k_mkl, &alpha, \
        matdescra, val, idx, ptrb, ptre, x, &beta, y);
  } else {
    // use built-in implementaion
    const float* val = a.GetVal();
    const MKL_INT* idx = a.GetIdx();
    const MKL_INT* ptrb = a.GetPtrb();
    const MKL_INT* ptre = a.GetPtre();
    const float* pb = b.GetDataPtr();
    float* pc = c.GetDataPtr();
    for (std::size_t im = 0; im < m; ++im) {
      float valCur = 0.0;
      for (MKL_INT eleIdx = ptrb[im]; eleIdx < ptre[im]; ++eleIdx) {
        valCur += val[eleIdx] * pb[idx[eleIdx]];
      } // ENDFOR: eleIdx
      pc[im] = valCur;
    } // ENDFOR: im
  } // ENDIF: enblMKL
}

void SprsMatMatProd(const SprsArray<float>& a, \
    const Array<float>& b, const bool enblMKL, Array<float>& c) {
  // obtain basic variables
  std::size_t m = a.GetRowCnt();
  std::size_t k = a.GetColCnt();
  std::size_t n = b.GetDimLen(1);

  // verify the input/output arrays' size
  if (b.GetDimLen(0) != k) {
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
    char transa = 'n';
    MKL_INT m_mkl = m;
    MKL_INT n_mkl = n;
    MKL_INT k_mkl = k;
    float alpha = 1.0;
    char matdescra[] = "G__C";
    float* val = a.GetVal();
    MKL_INT* idx = a.GetIdx();
    MKL_INT* ptrb = a.GetPtrb();
    MKL_INT* ptre = a.GetPtre();
    float* b_mkl = b.GetDataPtr();
    MKL_INT ldb = k;
    float beta = 0.0;
    float* c_mkl = c.GetDataPtr();
    MKL_INT ldc = n;
    mkl_scsrmm(&transa, &m_mkl, &n_mkl, &k_mkl, &alpha, \
        matdescra, val, idx, ptrb, ptre, b_mkl, &ldb, &beta, c_mkl, &ldc);
  } else {
    // use built-in implementaion
    const float* val = a.GetVal();
    const MKL_INT* idx = a.GetIdx();
    const MKL_INT* ptrb = a.GetPtrb();
    const MKL_INT* ptre = a.GetPtre();
    float* pc = c.GetDataPtr();
    for (std::size_t in = 0; in < n; ++in) {
      for (std::size_t im = 0; im < m; ++im) {
        const float* pb = b.GetDataPtr() + in * k;
        float valCur = 0.0;
        for (MKL_INT eleIdx = ptrb[im]; eleIdx < ptre[im]; ++eleIdx) {
          valCur += val[eleIdx] * pb[idx[eleIdx]];
        } // ENDFOR: eleIdx
        pc[im * n + in] = valCur;
      } // ENDFOR im
    } // ENDFOR: in
    /*
    for (std::size_t im = 0; im < m; ++im) {
      float* pc = c.GetDataPtr() + im * n;
      for (std::size_t in = 0; in < n; ++in) {
        const float* pb = b.GetDataPtr() + in * k;
        float valCur = 0.0;
        for (MKL_INT eleIdx = ptrb[im]; eleIdx < ptre[im]; ++eleIdx) {
          valCur += val[eleIdx] * pb[idx[eleIdx]];
        } // ENDFOR: eleIdx
        pc[in] = valCur;
      } // ENDFOR: in
    } // ENDFOR: im
    */
  } // ENDIF: enblMKL
}

float CalcInPdVal(const float* pa, const float* pb, const std::size_t len) {
  float val = 0.0;
  for (std::size_t idx = 0; idx < len; ++idx) {
    val += pa[idx] * pb[idx];
  } // ENDFOR: idx
  return val;
}


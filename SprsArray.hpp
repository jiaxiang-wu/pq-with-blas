/*
  File Name: SprsArray.hpp
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Mon 01 Feb 2016 01:33:05 PM CST
 */

#ifndef SPRSARRAY_HPP_INCLUDED
#define SPRSARRAY_HPP_INCLUDED

#include <mkl.h>

#include "Array.hpp"

template<typename Dtype>
class SprsMat {
public:
  // constructor function
  inline SprArray
  // de-constructor function
  // generate a sparse matrix from a dense array
  void GnrtMat(const Array<Dtype>& array);
  // get the pointer <val_>
  Dtype* GetVal(void) { return val_; }
  // get the pointer <idx_>
  MKL_INT* GetIdx(void) { return idx_; }
  // get the pointer <ptrb_>
  MKL_INT* GetPtrb(void) { return ptrb_; }
  // get the pointer <ptre_>
  MKL_INT* GetPtre(void) { return ptre_; }

private:
  // the real-valued array of non-zero values
  Dtype* val_;
  // the column indexes of non-zero values
  MKL_INT* idx_;
  // the index of the first non-zero value of each row
  MKL_INT* ptrb_;
  // the index of the last non-zer value of each row
  MKL_INT* ptre_;
};

// Following are the implementations of the <SprsArray> class

void SprsMat::Create(const Array<Dtype>& array) {
  // verify the array
  if (array.GetDimCnt() != 2) {
    std::cout << "[ERROR] the input array must be 2-dimensional" << std::endl;
    exit(-1);
  } // ENDIF: array

  // obtain basic variables
  std::size_t rowCnt = array.GetDimLen(0);
  std::size_t colCnt = array.GetDimLen(1);
  std::size_t eleCnt = arary.GetEleCnt();
  std::size_t nnzCnt = 0;
  Dtype* pData = array.GetDataPtr();
  for (std::size_t eleIdx = 0; eleIdx < eleCnt; ++eleIdx) {
    if (ABS(pData[eleIdx]) > kEpsilon) {
      nnzCnt++;
    } // ENDIF: ABS
  } // ENDFOR: eleIdx

  // allocate space for pointers
  val_ = new Dtype[nnzCnt];
  idx_ = new MKL_INT[nnzCnt];
  ptrb_ = new MKL_INT[rowCnt];
  ptre_ = new MKL_INT[rowCnt];
}

void SprsMat::Delete(void) {
}

#define SPRSARRAY_HPP_INCLUDED


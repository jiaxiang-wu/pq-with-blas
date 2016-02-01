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
class SprsArray {
public:
  // constructor function
  inline SprsArray(void) : val_(NULL), idx_(NULL), ptrb_(NULL), ptre_(NULL) {}
  inline SprsArray(const Array<Dtype>& array);
  // de-constructor function
  inline ~SprsArray(void);
  // create a sparse array from the dense array
  inline void Create(const Array<Dtype>& array);
  // delete the sparse array
  inline void Delete(void);
  // obtain the pointer <val_>
  inline Dtype* GetVal(void) const;
  // obtain the pointer <idx_>
  inline MKL_INT* GetIdx(void) const;
  // obtain the pointer <ptrb_>
  inline MKL_INT* GetPtrb(void) const;
  // obtain the pointer <ptre_>
  inline MKL_INT* GetPtre(void) const;

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

SprsArray::SprsArray(const Array<Dtype>& array) {
  // set all pointers to <NULL>
  val_ = NULL;
  idx_ = NULL;
  ptrb_ = NULL;
  ptre_ = NULL;

  // call <Create> function for array conversion
  Create(array);
}

SprsArray::~SprsArray(void) {
  Delete();
}

void SprsArray::Create(const Array<Dtype>& array) {
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
  const Dtype* pData = array.GetDataPtr();
  for (std::size_t eleIdx = 0; eleIdx < eleCnt; ++eleIdx) {
    if (ABS(pData[eleIdx]) > kEpsilon) {
      nnzCnt++;
    } // ENDIF: ABS
  } // ENDFOR: eleIdx

  // release space occupied by previous pointers (if any)
  Delete();

  // allocate space for pointers
  val_ = new Dtype[nnzCnt];
  idx_ = new MKL_INT[nnzCnt];
  ptrb_ = new MKL_INT[rowCnt];
  ptre_ = new MKL_INT[rowCnt];

  // convert the dense array to CSR format, zero-based indexing)
  std::size_t nnzIdx = 0;
  for (std::size_t rowIdx = 0; rowIdx < rowCnt; ++rowIdx) {
    // initialize variables for the current row
    const Dtype* pData = array.GetDataPtr() + rowIdx * colCnt;
    bool isFirst = true;

    // scan through the current row
    for (std::size_t colIdx = 0; colIdx < colCnt; ++colIdx) {
      if (ABS(pData[colIdx]) > kEpsilon) {
        val_[nnzIdx] = pData[colIdx];
        idx_[nnzIdx] = colIdx;
        if (isFirst) {
          isFirst = false;
          ptrb_[rowIdx] = nnzIdx;
        } // ENDIF: isFirst
        ptre_[rowIdx] = ++nnzIdx;
      } // ENDIF: ABS
    } // ENDFOR: colIdx
  } // ENDFOR: rowIdx
}

void SprsArray::Delete(void) {
  // delete all pointers
  if (val_ != NULL) {
    delete[] val_;
    val_ = NULL;
  } // ENDIF: val_
  if (idx_ != NULL) {
    delete[] idx_;
    idx_ = NULL;
  } // ENDIF: idx_;
  if (ptrb_ != NULL) {
    delete[] ptrb_;
    ptrb_ = NULL;
  } // ENDIF: ptrb_
  if (ptre_ != NULL) {
    delete[] ptre_;
    ptre_ = NULL;
  } // ENDIF: ptre_;
}

Dtype* SprsArray::GetVal(void) const {
  return val_;
}

MKL_INT* SprsArray::GetIdx(void) const {
  return idx_;
}

MKL_INT* SprsArray::GetPtrb(void) const {
  return ptrb_;
}

MKL_INT* SprsArray::GetPtre(void) const {
  return ptre_;
}

#define SPRSARRAY_HPP_INCLUDED


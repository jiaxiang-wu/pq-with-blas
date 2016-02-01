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

const float kEpsilon = 0.000001;

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
  // obtain the number of rows
  inline std::size_t GetRowCnt(void) const;
  // obtain the number of columns
  inline std::size_t GetColCnt(void) const;
  // obtain the number of non-zero elements
  inline std::size_t GetNnzCnt(void) const;
  // display the size information
  inline void DispSiz(void) const;

private:
  // the number of rows
  std::size_t rowCnt_;
  // the number of columns
  std::size_t colCnt_;
  // the number of non-zero elements
  std::size_t nnzCnt_;
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

template<typename Dtype>
SprsArray<Dtype>::SprsArray(const Array<Dtype>& array) {
  // set all pointers to <NULL>
  val_ = NULL;
  idx_ = NULL;
  ptrb_ = NULL;
  ptre_ = NULL;

  // call <Create> function for array conversion
  Create(array);
}

template<typename Dtype>
SprsArray<Dtype>::~SprsArray(void) {
  Delete();
}

template<typename Dtype>
void SprsArray<Dtype>::Create(const Array<Dtype>& array) {
  // verify the array
  if (array.GetDimCnt() != 2) {
    std::cout << "[ERROR] the input array must be 2-dimensional" << std::endl;
    exit(-1);
  } // ENDIF: array

  // obtain basic variables
  rowCnt_ = array.GetDimLen(0);
  colCnt_ = array.GetDimLen(1);
  nnzCnt_ = 0;
  std::size_t eleCnt = array.GetEleCnt();
  const Dtype* pData = array.GetDataPtr();
  for (std::size_t eleIdx = 0; eleIdx < eleCnt; ++eleIdx) {
    if (ABS(pData[eleIdx]) > kEpsilon) {
      nnzCnt_++;
    } // ENDIF: ABS
  } // ENDFOR: eleIdx

  // release space occupied by previous pointers (if any)
  Delete();

  // allocate space for pointers
  val_ = new Dtype[nnzCnt_];
  idx_ = new MKL_INT[nnzCnt_];
  ptrb_ = new MKL_INT[rowCnt_];
  ptre_ = new MKL_INT[rowCnt_];

  // convert the dense array to CSR format, zero-based indexing)
  std::size_t nnzIdx = 0;
  for (std::size_t rowIdx = 0; rowIdx < rowCnt_; ++rowIdx) {
    // initialize variables for the current row
    const Dtype* pData = array.GetDataPtr() + rowIdx * colCnt_;
    bool isFirst = true;

    // scan through the current row
    for (std::size_t colIdx = 0; colIdx < colCnt_; ++colIdx) {
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

template<typename Dtype>
void SprsArray<Dtype>::Delete(void) {
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

template<typename Dtype>
Dtype* SprsArray<Dtype>::GetVal(void) const {
  return val_;
}

template<typename Dtype>
MKL_INT* SprsArray<Dtype>::GetIdx(void) const {
  return idx_;
}

template<typename Dtype>
MKL_INT* SprsArray<Dtype>::GetPtrb(void) const {
  return ptrb_;
}

template<typename Dtype>
MKL_INT* SprsArray<Dtype>::GetPtre(void) const {
  return ptre_;
}

template<typename Dtype>
std::size_t SprsArray<Dtype>::GetRowCnt(void) const {
  return rowCnt_;
}

template<typename Dtype>
std::size_t SprsArray<Dtype>::GetColCnt(void) const {
  return colCnt_;
}

template<typename Dtype>
std::size_t SprsArray<Dtype>::GetNnzCnt(void) const {
  return nnzCnt_;
}

template<typename Dtype>
void SprsArray<Dtype>::DispSiz(void) const {
  std::cout << "[INFO] # of nnz elements: " << nnzCnt_ << std::endl;
  std::cout << "[INFO] Dim #0: " << rowCnt_ << std::endl;
  std::cout << "[INFO] Dim #1: " << colCnt_ << std::endl;
}

#endif // SPRSARRAY_HPP_INCLUDED


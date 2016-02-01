/*
  File Name: SprsMat.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Mon 01 Feb 2016 11:05:53 AM CST
 */

#ifndef SPRSMAT_H_INCLUDED
#define SPRSMAT_H_INCLUDED

#include <mkl.h>

#include "Array.hpp"

template<typename Dtype>
class SprsMat {
public:
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

#endif // SPRSMAT_H_INCLUDED


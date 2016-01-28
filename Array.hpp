/*
  File Name: Array.hpp
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 27 Jan 2016 08:37:48 PM CST
 */

#ifndef ARRAY_HPP_INCLUDED
#define ARRAY_HPP_INCLUDED

#include <vector>
#include <iostream>

typedef std::vector<std::size_t> ArraySiz;

template <typename Dtype>
class Array {
public:
  // constructor function
  Array(void) : siz_(ArraySiz(0)), pData_(NULL) {}
  Array(const ArraySiz& siz) {
    Create(siz);
  }

  // de-constructor function
  ~Array(void) {
    Destroy();
  }

  // create an N-dimensional array
  void Create(const ArraySiz& siz) {
    siz_ = siz;
    eleCnt_ = 1;
    for (std::size_t idx = 0; idx < siz_.size(); ++idx) {
      eleCnt_ *= siz_[idx];
    } // ENDFOR: idx
    pData_ = new Dtype[eleCnt_];
  }

  // destroy the array
  void Destroy(void) {
    siz_.swap(ArraySiz(0));
    eleCnt_ = 0;
    if (pData_ != NULL) {
      delete[] pData_;
      pData_ = NULL;
    } // ENDIF: pData_
  }

  // obtain the data pointer
  Dtype* GetDataPtr(void) const {
    return pData_;
  }

  // obtain the number of dimensions
  std::size_t GetDimCnt(void) const {
    return siz_.size();
  }

  // obtain the length of the x-th dimension
  std::size_t GetDimLen(const std::size_t idx) const {
    return siz_[idx];
  }

  // obtain the pointer stepsize of the x-th dimension
  std::size_t GetDimStp(const std::size_t idx) const {
    return (idx == siz_.size() - 1) ? 1 : siz_[idx + 1] * GetDimStp(idx + 1);
  }

  // obtain the total number of elements
  std::size_t GetEleCnt(void) const {
    return eleCnt_;
  }

  // resize the N-dimensional array
  void Resize(const ArraySiz& siz) {
    if (eleCnt_ != GetEleCnt(siz)) { // re-allocation needed
      Destroy();
      Create(siz);
    } else { // re-allocation not needed
      siz_ = siz;
    } // ENDIF: GetEleCnt()
  }

  // display the size information
  void DispSiz(void) const {
    std::cout << "# of elements: " << eleCnt_ << std::endl;
    for (std::size_t idx = 0; idx < siz_.size(); ++idx) {
      std::cout << "Dim #" << idx + 1 << ": " << siz_[idx] << std::endl;
    } // ENDFOR: idx
  }

private:
  // the length of each dimension
  ArraySiz siz_;
  // the number of elements
  std::size_t eleCnt_;
  // the data pointer
  Dtype* pData_;
};

#endif // ARRAY_HPP_INCLUDED


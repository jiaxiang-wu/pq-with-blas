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
  inline Array(void) : siz_(ArraySiz(0)), pData_(NULL) {}
  inline Array(const ArraySiz& siz);
  // de-constructor function
  inline ~Array(void);
  // create an N-dimensional array
  inline void Create(const ArraySiz& siz);
  // delete the array
  inline void Delete(void);
  // obtain the data pointer
  inline Dtype* GetDataPtr(void) const;
  // obtain the number of dimensions
  inline std::size_t GetDimCnt(void) const;
  // obtain the length of the x-th dimension
  inline std::size_t GetDimLen(const std::size_t idx) const;
  // obtain the pointer stepsize of the x-th dimension
  inline std::size_t GetDimStp(const std::size_t idx) const;
  // obtain the total number of elements
  inline std::size_t GetEleCnt(void) const;
  // resize the N-dimensional array
  inline void Resize(const ArraySiz& siz);
  // display the size information
  inline void DispSiz(void) const;

private:
  // the length of each dimension
  ArraySiz siz_;
  // the number of elements
  std::size_t eleCnt_;
  // the data pointer
  Dtype* pData_;
};

// Following are the implementations of the <Array> class

template<typename Dtype>
Array<Dtype>::Array(const ArraySiz& siz) {
  Create(siz);
}

template<typename Dtype>
Array<Dtype>::~Array(void) {
  Delete();
}

template<typename Dtype>
void Array<Dtype>::Create(const ArraySiz& siz) {
  siz_ = siz;
  eleCnt_ = 1;
  for (std::size_t idx = 0; idx < siz_.size(); ++idx) {
    eleCnt_ *= siz_[idx];
  } // ENDFOR: idx
  pData_ = new Dtype[eleCnt_];
}

template<typename Dtype>
void Array<Dtype>::Delete(void) {
  siz_.swap(ArraySiz(0));
  eleCnt_ = 0;
  if (pData_ != NULL) {
    delete[] pData_;
    pData_ = NULL;
  } // ENDIF: pData_
}

template<typename Dtype>
Dtype* Array<Dtype>::GetDataPtr(void) const {
  return pData_;
}

template<typename Dtype>
std::size_t Array<Dtype>::GetDimCnt(void) const {
  return siz_.size();
}

template<typename Dtype>
std::size_t Array<Dtype>::GetDimLen(const std::size_t idx) const {
  return siz_[idx];
}

template<typename Dtype>
std::size_t Array<Dtype>::GetDimStp(const std::size_t idx) const {
  return (idx == siz_.size() - 1) ? 1 : siz_[idx + 1] * GetDimStp(idx + 1);
}

template<typename Dtype>
std::size_t Array<Dtype>::GetEleCnt(void) const {
  return eleCnt_;
}

template<typename Dtype>
void Array<Dtype>::Resize(const ArraySiz& siz) {
  if (eleCnt_ != GetEleCnt(siz)) { // re-allocation needed
    Delete();
    Create(siz);
  } else { // re-allocation not needed
    siz_ = siz;
  } // ENDIF: eleCnt_
}

template<typename Dtype>
void Array<Dtype>::DispSiz(void) const {
  std::cout << "# of elements: " << eleCnt_ << std::endl;
  for (std::size_t idx = 0; idx < siz_.size(); ++idx) {
    std::cout << "Dim #" << idx << ": " << siz_[idx] << std::endl;
  } // ENDFOR: idx
}

#endif // ARRAY_HPP_INCLUDED


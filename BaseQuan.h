/*
  File Name: BaseQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 02:31:51 PM CST
 */

#ifndef BASEQUAN_H_INCLUDED
#define BASEQUAN_H_INCLUDED

#include "Array.hpp"

class BaseQuan {
public:
  // fill-up essential arrays with random number
  void Fillup(void);
  // measure the time consumption of processing a single query
  void MsrSngTime(void);
  // measure the time consumption of processing multiple queries
  void MsrMulTime(void);

private:
  // the number of feature dimensions
  std::size_t featCnt_;
  // the number of sub-codebooks
  std::size_t scbkCnt_;
  // the number of sub-codewords in each sub-codebook
  std::size_t scwdCnt_;
  // the number of multiple queries within a batch
  std::size_t quryCnt_;
  // the number of repeative runs (for more stable time measurement)
  std::size_t reptCnt_;

private:
  // the array containing a single query
  Array<float> qurySng;
  // the array containing multiple queries
  Array<float> quryMul;
  // the array containing all sub-codebooks
  Array<float> scbkLst;
};

#endif // BASEQUAN_H_INCLUDED


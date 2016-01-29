/*
  File Name: BaseQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 02:31:51 PM CST
 */

#ifndef BASEQUAN_H_INCLUDED
#define BASEQUAN_H_INCLUDED

#include <vector>

#include "Array.hpp"

class BaseQuan {
public:
  // allocate and fill-up a list of arrays of the same size
  void AllctAndFill(const ArraySiz& siz, Array<float>& array);
  void AllctAndFill(const std::size_t len, \
      const ArraySiz& siz, std::vector<Array<float> >& arrays);

protected:
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

protected:
  // the number of feature dimensions for each sub-codebook
  std::size_t featCntPerScbk_;

protected:
  // the original query (single)
  ArraySiz quryOrgSngSiz_;
  Array<float> quryOrgSng_;
  // the original queries (multiple)
  ArraySiz quryOrgMulSiz_;
  Array<float> quryOrgMul_;
  // the list of decomposed sub-queries (single)
  ArraySiz quryDcpSngSiz_;
  std::vector<Array<float> > quryDcpSng_;
  // the list of decomposed sub-queries (multiple)
  ArraySiz quryDcpMulSiz_;
  std::vector<Array<float> > quryDcpMul_;
  // the list of sub-codebooks
  ArraySiz scbkLstSiz_;
  std::vector<Array<float> > scbkLst_;
  // the list of pre-computed inner products (single)
  ArraySiz inPdSngSiz_;
  std::vector<Array<float> > inPdSng_;
  // the list of pre-computed inner products (multiple)
  ArraySiz inPdMulSiz_;
  std::vector<Array<float> > inPdMul_;
};

#endif // BASEQUAN_H_INCLUDED


/*
  File Name: ProdQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 02:55:41 PM CST
 */

#include "ProdQuan.h"

#include "BlasWrapper.h"

void ProdQuan::SetParam(const ProdQuanParam& param) {
  // set-up PQ's parameters
  featCnt_ = param.featCnt;
  scbkCnt_ = param.scbkCnt;
  scwdCnt_ = param.scwdCnt;
  quryCnt_ = param.quryCnt;
  reptCnt_ = param.reptCnt;

  // compute other (derived) parameters
  featCntPerScbk_ = featCnt_ / scbkCnt_;
}

void ProdQuan::Fillup(void) {
  // fill-up the list of decomposed sub-queries (single)
  qurySngSiz_.resize(2);
  qurySngSiz_[0] = 1;
  qurySngSiz_[1] = featCntPerScbk_;
  qurySng_.clear();
  qurySng_.resize(scbkCnt_, Array<float>(qurySngSiz_));

  // fill-up the list of decomposed sub-queries (multiple)
  quryMulSiz_.resize(2);
  quryMulSiz_[0] = quryCnt_;
  quryMulSiz_[1] = featCntPerScbk_;
  quryMul_.clear();
  quryMul_.resize(scbkCnt_, Array<float>(quryMulSiz_));

  // fill-up the list of sub-codebooks
  scbkLstSiz_.resize(2);
  scbkLstSiz_[0] = scwdCnt_;
  scbkLstSiz_[1] = featCntPerScbk_;
  scbkLst_.clear();
  scbkLst_.resize(scbkCnt_, Array<float>(scbkLstSiz_));

  // fill-up the list of pre-computed inner products (single)
  inPdSngSiz_.resize(2);
  inPdSngSiz_[0] = scwdCnt_;
  inPdSngSiz_[1] = 1;
  inPdSng_.clear();
  inPdSng_.resize(scbkCnt_, Array<float>(inPdSngSiz_));

  // fill-up the list of pre-computed inner products (multiple)
  inPdMulSiz_.resize(2);
  inPdMulSiz_[0] = scwdCnt_;
  inPdMulSiz_[1] = quryCnt_;
  inPdMul_.clear();
  inPdMul_.resize(scbkCnt_, Array<float>(inPdMulSiz_));

  // fill-up the above arrays with random numbers
  for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
    this->FillArray(qurySng_[scbkIdx]);
    this->FillArray(quryMul_[scbkIdx]);
    this->FillArray(scbkLst_[scbkIdx]);
    this->FillArray(inPdSng_[scbkIdx]);
    this->FillArray(inPdMul_[scbkIdx]);
  } // ENDFOR: scbkIdx
}

void ProdQuan::MsrSngTime(void) {
  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      VecMatProd(qurySng_[scbkIdx], scbkLst_[scbkIdx], inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void ProdQuan::MsrMulTime(void) {
  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      MatMatProd(quryMul_[scbkIdx], scbkLst_[scbkIdx], inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


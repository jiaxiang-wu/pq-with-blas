/*
  File Name: ProdQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 02:55:41 PM CST
 */

#include "ProdQuan.h"

#include <iostream>
#include <cstring>

#include "BlasWrapper.h"

void ProdQuan::SetParam(const ProdQuanParam& param) {
  // display the greeting message
  std::cout << "[INFO] entering ProdQuan::SetParam()" << std::endl;

  // set-up PQ's parameters
  featCnt_ = param.featCnt;
  scbkCnt_ = param.scbkCnt;
  scwdCnt_ = param.scwdCnt;
  quryCnt_ = param.quryCnt;
  reptCnt_ = param.reptCnt;

  // compute other (derived) parameters
  featCntPerScbk_ = featCnt_ / scbkCnt_;

  // display all parameters
  std::cout << "[INFO] featCnt = " << featCnt_ << std::endl;
  std::cout << "[INFO] scbkCnt = " << scbkCnt_ << std::endl;
  std::cout << "[INFO] scwdCnt = " << scwdCnt_ << std::endl;
  std::cout << "[INFO] quryCnt = " << quryCnt_ << std::endl;
  std::cout << "[INFO] reptCnt = " << reptCnt_ << std::endl;
  std::cout << "[INFO] featCntPerScbk = " << featCntPerScbk_ << std::endl;
}

void ProdQuan::Fillup(void) {
  // display the greeting message
  std::cout << "[INFO] entering ProdQuan::Fillup()" << std::endl;

  // compute the size of each array
  quryOrgSngSiz_.resize(2);
  quryOrgSngSiz_[0] = 1;
  quryOrgSngSiz_[1] = featCnt_;
  quryOrgMulSiz_.resize(2);
  quryOrgMulSiz_[0] = quryCnt_;
  quryOrgMulSiz_[1] = featCnt_;
  quryDcpSngSiz_.resize(2);
  quryDcpSngSiz_[0] = 1;
  quryDcpSngSiz_[1] = featCntPerScbk_;
  quryDcpMulSiz_.resize(2);
  quryDcpMulSiz_[0] = quryCnt_;
  quryDcpMulSiz_[1] = featCntPerScbk_;
  scbkLstSiz_.resize(2);
  scbkLstSiz_[0] = scwdCnt_;
  scbkLstSiz_[1] = featCntPerScbk_;
  inPdSngSiz_.resize(2);
  inPdSngSiz_[0] = scwdCnt_;
  inPdSngSiz_[1] = 1;
  inPdMulSiz_.resize(2);
  inPdMulSiz_[0] = scwdCnt_;
  inPdMulSiz_[1] = quryCnt_;

  // fill-up the above arrays with random numbers
  AllctAndFill(quryOrgSngSiz_, quryOrgSng_);
  AllctAndFill(quryOrgMulSiz_, quryOrgMul_);
  AllctAndFill(scbkCnt_, quryDcpSngSiz_, quryDcpSng_);
  AllctAndFill(scbkCnt_, quryDcpMulSiz_, quryDcpMul_);
  AllctAndFill(scbkCnt_, scbkLstSiz_, scbkLst_);
  AllctAndFill(scbkCnt_, inPdSngSiz_, inPdSng_);
  AllctAndFill(scbkCnt_, inPdMulSiz_, inPdMul_);
}

void ProdQuan::MsrSngTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering ProdQuan::MsrSngTime()" << std::endl;

  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    // split the query vector into sub-query vectors
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      const float* pSrc = quryOrgSng_.GetDataPtr() + scbkIdx * featCntPerScbk_;
      float* pDst = quryDcpSng_[scbkIdx].GetDataPtr();
      memcpy(pDst, pSrc, sizeof(float) * featCntPerScbk_);
    } // ENDFOR: scbkIdx

    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      VecMatProd(scbkLst_[scbkIdx], \
          quryDcpSng_[scbkIdx], enblMKL, inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void ProdQuan::MsrMulTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering ProdQuan::MsrMulTime()" << std::endl;

  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    // split the query vectors into sub-query vectors
    for (std::size_t quryIdx = 0; quryIdx < quryCnt_; ++quryIdx) {
      for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
        const float* pSrc = quryOrgMul_.GetDataPtr() \
            + quryIdx * featCnt_ + scbkIdx * featCntPerScbk_;
        float* pDst = quryDcpMul_[scbkIdx].GetDataPtr() \
            + quryIdx * featCntPerScbk_;
        memcpy(pDst, pSrc, sizeof(float) * featCntPerScbk_);
      }
    } // ENDFOR: quryIdx

    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      MatMatProd(scbkLst_[scbkIdx], \
          quryDcpMul_[scbkIdx], enblMKL, inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


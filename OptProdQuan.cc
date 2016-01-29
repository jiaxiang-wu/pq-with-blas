/*
  File Name: OptProdQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Fri 29 Jan 2016 04:36:27 PM CST
 */

#include "OptProdQuan.h"

#include <iostream>
#include <cstring>

#include "BlasWrapper.h"

void OptProdQuan::SetParam(const OptProdQuanParam& param) {
  // display the greeting message
  std::cout << "[INFO] entering OptProdQuan::SetParam()" << std::endl;

  // set-up PQ's parameters
  featCnt_ = param.featCnt;
  scbkCnt_ = param.scbkCnt;
  scwdCnt_ = param.scwdCnt;
  quryCnt_ = param.quryCnt;
  reptCnt_ = param.reptCnt;
  featCntPrj_ = param.featCntPrj;

  // compute other (derived) parameters
  featCntPrjPerScbk_ = featCntPrj_ / scbkCnt_;

  // display all parameters
  std::cout << "[INFO] featCnt = " << featCnt_ << std::endl;
  std::cout << "[INFO] scbkCnt = " << scbkCnt_ << std::endl;
  std::cout << "[INFO] scwdCnt = " << scwdCnt_ << std::endl;
  std::cout << "[INFO] quryCnt = " << quryCnt_ << std::endl;
  std::cout << "[INFO] reptCnt = " << reptCnt_ << std::endl;
  std::cout << "[INFO] featCntPrj = " << featCntPrj_ << std::endl;
  std::cout << "[INFO] featCntPrjPerScbk = " << featCntPrjPerScbk_ << std::endl;
}

void OptProdQuan::Fillup(void) {
  // display the greeting message
  std::cout << "[INFO] entering OptProdQuan::Fillup()" << std::endl;

  // compute the size of each array
  quryOrgSngSiz_.resize(2);
  quryOrgSngSiz_[0] = 1;
  quryOrgSngSiz_[1] = featCnt_;
  quryOrgMulSiz_.resize(2);
  quryOrgMulSiz_[0] = quryCnt_;
  quryOrgMulSiz_[1] = featCnt_;
  matrPrjSiz_.resize(2);
  matrPrjSiz_[0] = featCntPrj_;
  matrPrjSiz_[1] = featCnt_;
  quryPrjSngSiz_.resize(2);
  quryPrjSngSiz_[0] = 1;
  quryPrjSngSiz_[1] = featCntPrj_;
  quryPrjMulSiz_.resize(2);
  quryPrjMulSiz_[0] = quryCnt_;
  quryPrjMulSiz_[1] = featCntPrj_;
  quryDcpSngSiz_.resize(2);
  quryDcpSngSiz_[0] = 1;
  quryDcpSngSiz_[1] = featCntPrjPerScbk_;
  quryDcpMulSiz_.resize(2);
  quryDcpMulSiz_[0] = quryCnt_;
  quryDcpMulSiz_[1] = featCntPrjPerScbk_;
  scbkLstSiz_.resize(2);
  scbkLstSiz_[0] = scwdCnt_;
  scbkLstSiz_[1] = featCntPrjPerScbk_;
  inPdSngSiz_.resize(2);
  inPdSngSiz_[0] = scwdCnt_;
  inPdSngSiz_[1] = 1;
  inPdMulSiz_.resize(2);
  inPdMulSiz_[0] = scwdCnt_;
  inPdMulSiz_[1] = quryCnt_;

  // fill-up the above arrays with random numbers
  AllctAndFill(quryOrgSngSiz_, quryOrgSng_);
  AllctAndFill(quryOrgMulSiz_, quryOrgMul_);
  AllctAndFill(matrPrjSiz_, matrPrj_);
  AllctAndFill(quryPrjSngSiz_, quryPrjSng_);
  AllctAndFill(quryPrjMulSiz_, quryPrjMul_);
  AllctAndFill(scbkCnt_, quryDcpSngSiz_, quryDcpSng_);
  AllctAndFill(scbkCnt_, quryDcpMulSiz_, quryDcpMul_);
  AllctAndFill(scbkCnt_, scbkLstSiz_, scbkLst_);
  AllctAndFill(scbkCnt_, inPdSngSiz_, inPdSng_);
  AllctAndFill(scbkCnt_, inPdMulSiz_, inPdMul_);
}

void OptProdQuan::MsrSngTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering OptProdQuan::MsrSngTime()" << std::endl;

  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    // apply the projection matrix on the query vector
    MatMatProd(quryOrgSng_, matrPrj_, enblMKL, quryPrjSng_);

    // split the query vector into sub-query vectors
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      const float* pSrc = quryPrjSng_.GetDataPtr() \
          + scbkIdx * featCntPrjPerScbk_;
      float* pDst = quryDcpSng_[scbkIdx].GetDataPtr();
      memcpy(pDst, pSrc, sizeof(float) * featCntPrjPerScbk_);
    } // ENDFOR: scbkIdx

    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      VecMatProd(scbkLst_[scbkIdx], \
          quryDcpSng_[scbkIdx], enblMKL, inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void OptProdQuan::MsrMulTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering OptProdQuan::MsrMulTime()" << std::endl;

  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    // apply the projection matrix on the query vector
    MatMatProd(quryOrgMul_, matrPrj_, enblMKL, quryPrjMul_);

    // split the query vectors into sub-query vectors
    for (std::size_t quryIdx = 0; quryIdx < quryCnt_; ++quryIdx) {
      for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
        const float* pSrc = quryPrjMul_.GetDataPtr() \
            + quryIdx * featCntPrj_ + scbkIdx * featCntPrjPerScbk_;
        float* pDst = quryDcpMul_[scbkIdx].GetDataPtr() \
            + quryIdx * featCntPrjPerScbk_;
        memcpy(pDst, pSrc, sizeof(float) * featCntPrjPerScbk_);
      }
    } // ENDFOR: quryIdx

    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      MatMatProd(scbkLst_[scbkIdx], \
          quryDcpMul_[scbkIdx], enblMKL, inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


/*
  File Name: SprsCompQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 03 Feb 2016 03:06:25 PM CST
 */

#include "SprsCompQuan.h"

#include <iostream>
#include <cstring>

#include "BlasWrapper.h"

inline float GnrtRndNum(void) {
  return static_cast<float>(rand() % RAND_MAX) / (RAND_MAX - 1);
}

SprsCompQuanParam::SprsCompQuanParam(\
    const BaseQuanParam& param, const float sprsRat) {
  // set-up SCQ's parameters
  featCnt_ = param.featCnt_;
  scbkCnt_ = param.scbkCnt_;
  scwdCnt_ = param.scwdCnt_;
  quryCnt_ = param.quryCnt_;
  btchSiz_ = param.btchSiz_;
  sprsRat_ = sprsRat;
}

void SprsCompQuan::SetParam(const SprsCompQuanParam& param) {
  // display the greeting message
  std::cout << "[INFO] entering SprsCompQuan::SetParam()" << std::endl;

  // set-up SCQ's parameters
  param_ = param;

  // display all parameters
  std::cout << "[INFO] featCnt = " << param_.featCnt_ << std::endl;
  std::cout << "[INFO] scbkCnt = " << param_.scbkCnt_ << std::endl;
  std::cout << "[INFO] scwdCnt = " << param_.scwdCnt_ << std::endl;
  std::cout << "[INFO] quryCnt = " << param_.quryCnt_ << std::endl;
  std::cout << "[INFO] btchSiz = " << param_.btchSiz_ << std::endl;
  std::cout << "[INFO] sprsRat = " << param_.sprsRat_ << std::endl;
}

void SprsCompQuan::Fillup(void) {
  // display the greeting message
  std::cout << "[INFO] entering SprsCompQuan::Fillup()" << std::endl;

  // compute the size of each array
  quryOrgSngSiz_.resize(2); // differs from PQ, OPQ, and CQ
  quryOrgSngSiz_[0] = param_.featCnt_;
  quryOrgSngSiz_[1] = 1;
  quryOrgMulSiz_.resize(2); // differs from PQ, OPQ, and CQ
  quryOrgMulSiz_[0] = param_.featCnt_;
  quryOrgMulSiz_[1] = param_.btchSiz_;
  scbkLstSiz_.resize(2);
  scbkLstSiz_[0] = param_.scwdCnt_;
  scbkLstSiz_[1] = param_.featCnt_;
  inPdSngSiz_.resize(2);
  inPdSngSiz_[0] = param_.scwdCnt_;
  inPdSngSiz_[1] = 1;
  inPdMulSiz_.resize(2);
  inPdMulSiz_[0] = param_.scwdCnt_;
  inPdMulSiz_[1] = param_.btchSiz_;

  // fill-up the above arrays with random numbers
  AllctAndFill(quryOrgSngSiz_, quryOrgSng_);
  AllctAndFill(quryOrgMulSiz_, quryOrgMul_);
  AllctAndFill(param_.scbkCnt_, scbkLstSiz_, scbkLst_);
  AllctAndFill(param_.scbkCnt_, inPdSngSiz_, inPdSng_);
  AllctAndFill(param_.scbkCnt_, inPdMulSiz_, inPdMul_);

  // randomly set elements in <scbkLst_> to zeros
  for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
    float* p = scbkLst_[scbkIdx].GetDataPtr();
    std::size_t eleCnt = scbkLst_[scbkIdx].GetEleCnt();
    for (std::size_t eleIdx = 0; eleIdx < eleCnt; ++eleIdx) {
      if (GnrtRndNum() > param_.sprsRat_) {
        p[eleIdx] = 0.0;
      } // ENDIF: GnrtRndNum
    } // ENDFOR: eleIdx
  } // ENDFOR: scbkIdx

  // generate the sparse version of <scbkLst_>
  sprsScbkLst_.resize(param_.scbkCnt_);
  for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
    sprsScbkLst_[scbkIdx].Create(scbkLst_[scbkIdx]);
  } // ENDFOR: scbkIdx
}

void SprsCompQuan::MsrSngTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering SprsCompQuan::MsrSngTime()" << std::endl;

  // execute multiple runs for stable time measurement
  std::size_t reptCnt = param_.quryCnt_; // single query
  for (std::size_t reptIdx = 0; reptIdx < reptCnt; ++reptIdx) {
    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
      SprsMatVecProd(sprsScbkLst_[scbkIdx], \
          quryOrgSng_, enblMKL, inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void SprsCompQuan::MsrMulTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering SprsCompQuan::MsrMulTime()" << std::endl;

  // execute multiple runs for stable time measurement
  std::size_t reptCnt = param_.quryCnt_ / param_.btchSiz_; // multiple queries
  for (std::size_t reptIdx = 0; reptIdx < reptCnt; ++reptIdx) {
    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
      SprsMatMatProd(sprsScbkLst_[scbkIdx], \
          quryOrgMul_, enblMKL, inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


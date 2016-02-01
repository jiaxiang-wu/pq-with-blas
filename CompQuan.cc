/*
  File Name: CompQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Fri 29 Jan 2016 07:31:37 PM CST
 */

#include "CompQuan.h"

#include <iostream>
#include <cstring>

#include "BlasWrapper.h"

CompQuanParam::CompQuanParam(const BaseQuanParam& param) {
  // set-up CQ's parameters
  featCnt_ = param.featCnt_;
  scbkCnt_ = param.scbkCnt_;
  scwdCnt_ = param.scwdCnt_;
  quryCnt_ = param.quryCnt_;
  btchSiz_ = param.btchSiz_;
}

void CompQuan::SetParam(const CompQuanParam& param) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::SetParam()" << std::endl;

  // set-up PQ's parameters
  param_ = param;

  // display all parameters
  std::cout << "[INFO] featCnt = " << param_.featCnt_ << std::endl;
  std::cout << "[INFO] scbkCnt = " << param_.scbkCnt_ << std::endl;
  std::cout << "[INFO] scwdCnt = " << param_.scwdCnt_ << std::endl;
  std::cout << "[INFO] quryCnt = " << param_.quryCnt_ << std::endl;
  std::cout << "[INFO] btchSiz = " << param_.btchSiz_ << std::endl;
}

void CompQuan::Fillup(void) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::Fillup()" << std::endl;

  // compute the size of each array
  quryOrgSngSiz_.resize(2);
  quryOrgSngSiz_[0] = 1;
  quryOrgSngSiz_[1] = param_.featCnt_;
  quryOrgMulSiz_.resize(2);
  quryOrgMulSiz_[0] = param_.btchSiz_;
  quryOrgMulSiz_[1] = param_.featCnt_;
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
}

void CompQuan::MsrSngTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::MsrSngTime()" << std::endl;

  // execute multiple runs for stable time measurement
  std::size_t reptCnt = param_.quryCnt_; // single query
  for (std::size_t reptIdx = 0; reptIdx < reptCnt; ++reptIdx) {
    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
      MatVecProd(scbkLst_[scbkIdx], quryOrgSng_, enblMKL, inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void CompQuan::MsrMulTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::MsrMulTime()" << std::endl;

  // execute multiple runs for stable time measurement
  std::size_t reptCnt = param_.quryCnt_ / param_.btchSiz_; // multiple queries
  for (std::size_t reptIdx = 0; reptIdx < reptCnt; ++reptIdx) {
    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
      MatMatProd(scbkLst_[scbkIdx], quryOrgMul_, enblMKL, inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


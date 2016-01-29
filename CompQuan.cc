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

void CompQuan::SetParam(const CompQuanParam& param) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::SetParam()" << std::endl;

  // set-up PQ's parameters
  featCnt_ = param.featCnt;
  scbkCnt_ = param.scbkCnt;
  scwdCnt_ = param.scwdCnt;
  quryCnt_ = param.quryCnt;
  reptCnt_ = param.reptCnt;

  // display all parameters
  std::cout << "[INFO] featCnt = " << featCnt_ << std::endl;
  std::cout << "[INFO] scbkCnt = " << scbkCnt_ << std::endl;
  std::cout << "[INFO] scwdCnt = " << scwdCnt_ << std::endl;
  std::cout << "[INFO] quryCnt = " << quryCnt_ << std::endl;
  std::cout << "[INFO] reptCnt = " << reptCnt_ << std::endl;
}

void CompQuan::Fillup(void) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::Fillup()" << std::endl;

  // compute the size of each array
  quryOrgSngSiz_.resize(2);
  quryOrgSngSiz_[0] = 1;
  quryOrgSngSiz_[1] = featCnt_;
  quryOrgMulSiz_.resize(2);
  quryOrgMulSiz_[0] = quryCnt_;
  quryOrgMulSiz_[1] = featCnt_;
  scbkLstSiz_.resize(2);
  scbkLstSiz_[0] = scwdCnt_;
  scbkLstSiz_[1] = featCnt_;
  inPdSngSiz_.resize(2);
  inPdSngSiz_[0] = scwdCnt_;
  inPdSngSiz_[1] = 1;
  inPdMulSiz_.resize(2);
  inPdMulSiz_[0] = scwdCnt_;
  inPdMulSiz_[1] = quryCnt_;

  // fill-up the above arrays with random numbers
  AllctAndFill(quryOrgSngSiz_, quryOrgSng_);
  AllctAndFill(quryOrgMulSiz_, quryOrgMul_);
  AllctAndFill(scbkCnt_, scbkLstSiz_, scbkLst_);
  AllctAndFill(scbkCnt_, inPdSngSiz_, inPdSng_);
  AllctAndFill(scbkCnt_, inPdMulSiz_, inPdMul_);
}

void CompQuan::MsrSngTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::MsrSngTime()" << std::endl;

  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      VecMatProd(scbkLst_[scbkIdx], quryOrgSng_, enblMKL, inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void CompQuan::MsrMulTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering CompQuan::MsrMulTime()" << std::endl;

  // execute multiple runs for stable time measurement
  for (std::size_t reptIdx = 0; reptIdx < reptCnt_; ++reptIdx) {
    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < scbkCnt_; ++scbkIdx) {
      MatMatProd(scbkLst_[scbkIdx], quryOrgMul_, enblMKL, inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


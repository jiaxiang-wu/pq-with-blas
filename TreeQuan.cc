/*
  File Name: TreeQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Mon 15 Feb 2016 02:47:03 PM CST
 */

#include "TreeQuan.h"

#include <iostream>
#include <cstring>

#include "BlasWrapper.h"

TreeQuanParam::TreeQuanParam(const BaseQuanParam& param) {
  // set-up TQ's parameters
  featCnt_ = param.featCnt_;
  scbkCnt_ = param.scbkCnt_;
  scwdCnt_ = param.scwdCnt_;
  quryCnt_ = param.quryCnt_;
  btchSiz_ = param.btchSiz_;
}

void DimConvParam::Init(const std::size_t featCnt, const std::size_t scbkCnt) {
  // pre-allocate space for vectors
  scbkIdxLstPri_.resize(featCnt);
  scbkIdxLstSec_.resize(featCnt);
  instIdxLstPri_.resize(featCnt);
  instIdxLstSec_.resize(featCnt);
  scbkLenLst_.clear();
  scbkLenLst_.resize(scbkCnt, 0);

  // randomly determine the feature dimension's assignment
  for (std::size_t featIdx = 0; featIdx < featCnt; ++featIdx) {
    while (true) {
      std::size_t scbkIdxPri = rand() % scbkCnt;
      std::size_t scbkIdxSec = rand() % scbkCnt;
      if (scbkIdxPri == scbkIdxSec) {
        continue;
      } else {
        scbkIdxLstPri_[featIdx] = scbkIdxPri;
        scbkIdxLstSec_[featIdx] = scbkIdxSec;
        instIdxLstPri_[featIdx] = scbkLenLst_[scbkIdxPri];
        instIdxLstSec_[featIdx] = scbkLenLst_[scbkIdxSec];
        scbkLenLst_[scbkIdxPri]++;
        scbkLenLst_[scbkIdxSec]++;
        break;
      } // ENDIF: scbkIdxPri
    } // ENDWHILE: true
  } // ENDFOR: featIdx
}

void TreeQuan::SetParam(const TreeQuanParam& param) {
  // display the greeting message
  std::cout << "[INFO] entering TreeQuan::SetParam()" << std::endl;

  // set-up TQ's parameters
  param_ = param;
  dimConvParam_.Init(param_.featCnt_, param_.scbkCnt_);

  // display all parameters
  std::cout << "[INFO] featCnt = " << param_.featCnt_ << std::endl;
  std::cout << "[INFO] scbkCnt = " << param_.scbkCnt_ << std::endl;
  std::cout << "[INFO] scwdCnt = " << param_.scwdCnt_ << std::endl;
  std::cout << "[INFO] quryCnt = " << param_.quryCnt_ << std::endl;
  std::cout << "[INFO] btchSiz = " << param_.btchSiz_ << std::endl;
}

void TreeQuan::Fillup(void) {
  // display the greeting message
  std::cout << "[INFO] entering TreeQuan::Fillup()" << std::endl;

  // compute the size of each array
  quryOrgSngSiz_.resize(2);
  quryOrgSngSiz_[0] = 1;
  quryOrgSngSiz_[1] = param_.featCnt_;
  quryOrgMulSiz_.resize(2);
  quryOrgMulSiz_[0] = param_.btchSiz_;
  quryOrgMulSiz_[1] = param_.featCnt_;
  quryDcpSngSiz_.resize(2);
  quryDcpSngSiz_[0] = 1;
  quryDcpSngSiz_[1] = 0; // to be modified later
  quryDcpMulSiz_.resize(2);
  quryDcpMulSiz_[0] = param_.btchSiz_;
  quryDcpMulSiz_[1] = 0; // to be modified later
  scbkLstSiz_.resize(2);
  scbkLstSiz_[0] = param_.scwdCnt_;
  scbkLstSiz_[1] = 0; // to be modified later
  inPdSngSiz_.resize(2);
  inPdSngSiz_[0] = param_.scwdCnt_;
  inPdSngSiz_[1] = 1;
  inPdMulSiz_.resize(2);
  inPdMulSiz_[0] = param_.scwdCnt_;
  inPdMulSiz_[1] = param_.btchSiz_;

  // fill-up the above arrays with random numbers
  AllctAndFill(quryOrgSngSiz_, quryOrgSng_);
  AllctAndFill(quryOrgMulSiz_, quryOrgMul_);
  quryDcpSng_.resize(param_.scbkCnt_);
  quryDcpMul_.resize(param_.scbkCnt_);
  scbkLst_.resize(param_.scbkCnt_);
  for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
    std::size_t scbkLen = dimConvParam_.scbkLenLst_[scbkIdx];
    quryDcpSngSiz_[1] = scbkLen;
    quryDcpMulSiz_[1] = scbkLen;
    scbkLstSiz_[1] = scbkLen;
    AllctAndFill(quryDcpSngSiz_, quryDcpSng_[scbkIdx]);
    AllctAndFill(quryDcpMulSiz_, quryDcpMul_[scbkIdx]);
    AllctAndFill(scbkLstSiz_, scbkLst_[scbkIdx]);
  } // ENDFOR: scbkIdx
  AllctAndFill(param_.scbkCnt_, inPdSngSiz_, inPdSng_);
  AllctAndFill(param_.scbkCnt_, inPdMulSiz_, inPdMul_);
}

void TreeQuan::MsrSngTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering TreeQuan::MsrSngTime()" << std::endl;

  // execute multiple runs for stable time measurement
  std::size_t reptCnt = param_.quryCnt_; // single query
  for (std::size_t reptIdx = 0; reptIdx < reptCnt; ++reptIdx) {
    // split the query vector into sub-query vectors
    for (std::size_t featIdx = 0; featIdx < param_.featCnt_; ++featIdx) {
      std::size_t scbkIdxPri = dimConvParam_.scbkIdxLstPri_[featIdx];
      std::size_t scbkIdxSec = dimConvParam_.scbkIdxLstSec_[featIdx];
      std::size_t instIdxPri = dimConvParam_.instIdxLstPri_[featIdx];
      std::size_t instIdxSec = dimConvParam_.instIdxLstSec_[featIdx];
      const float* pSrc = quryOrgSng_.GetDataPtr() + featIdx;
      float* pDstPri = quryDcpSng_[scbkIdxPri].GetDataPtr() + instIdxPri;
      float* pDstSec = quryDcpSng_[scbkIdxSec].GetDataPtr() + instIdxSec;
      *pDstPri = *pSrc;
      *pDstSec = *pSrc;
    } // ENDFOR: featIdx

    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
      MatVecProd(scbkLst_[scbkIdx], \
          quryDcpSng_[scbkIdx], enblMKL, inPdSng_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}

void TreeQuan::MsrMulTime(const bool enblMKL) {
  // display the greeting message
  std::cout << "[INFO] entering TreeQuan::MsrMulTime()" << std::endl;

  // execute multiple runs for stable time measurement
  std::size_t reptCnt = param_.quryCnt_ / param_.btchSiz_; // multiple queries
  for (std::size_t reptIdx = 0; reptIdx < reptCnt; ++reptIdx) {
    // split the query vectors into sub-query vectors
    for (std::size_t btchIdx = 0; btchIdx < param_.btchSiz_; ++btchIdx) {
      for (std::size_t featIdx = 0; featIdx < param_.featCnt_; ++featIdx) {
        std::size_t scbkIdxPri = dimConvParam_.scbkIdxLstPri_[featIdx];
        std::size_t scbkIdxSec = dimConvParam_.scbkIdxLstSec_[featIdx];
        std::size_t instIdxPri = dimConvParam_.instIdxLstPri_[featIdx];
        std::size_t instIdxSec = dimConvParam_.instIdxLstSec_[featIdx];
        std::size_t scbkLenPri = dimConvParam_.scbkLenLst_[scbkIdxPri];
        std::size_t scbkLenSec = dimConvParam_.scbkLenLst_[scbkIdxSec];
        const float* pSrc = quryOrgMul_.GetDataPtr() \
            + btchIdx * param_.featCnt_ + featIdx;
        float* pDstPri = quryDcpMul_[scbkIdxPri].GetDataPtr() \
            + btchIdx * scbkLenPri + instIdxPri;
        float* pDstSec = quryDcpMul_[scbkIdxSec].GetDataPtr() \
            + btchIdx * scbkLenSec + instIdxSec;
        *pDstPri = *pSrc;
        *pDstSec = *pSrc;
      } // ENDFOR: featIdx
    } // ENDFOR: btchIdx

    // pre-compute the inner products
    for (std::size_t scbkIdx = 0; scbkIdx < param_.scbkCnt_; ++scbkIdx) {
      MatMatProd(scbkLst_[scbkIdx], \
          quryDcpMul_[scbkIdx], enblMKL, inPdMul_[scbkIdx]);
    } // ENDFOR: scbkIdx
  } // ENDFOR: reptIdx
}


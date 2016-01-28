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
}

void ProdQuan::Fillup(void) {
  //
}

void ProdQuan::MsrSngTime(void) {
}

void ProdQuan::MsrMulTime(void) {
}


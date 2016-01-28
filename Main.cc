/*
  File Name: Main.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 27 Jan 2016 07:55:01 PM CST
 */

#include <iostream>

#include "ProdQuan.h"
#include "StopWatch.hpp"

// define constant variables
const std::size_t kFeatCnt = 128;
const std::size_t kScbkCnt = 8;
const std::size_t kScwdCnt = 256;
const std::size_t kQuryCnt = 64;
const std::size_t kReptCnt = 10000;

void EvaProdQuan(void) {
  // declare objects
  ProdQuan prodQuanObj;
  ProdQuanParam param;
  StopWatch swSngQury;
  StopWatch swMulQury;

  // set-up PQ's parameters
  param.featCnt = kFeatCnt;
  param.scbkCnt = kScbkCnt;
  param.scwdCnt = kScwdCnt;
  param.quryCnt = kQuryCnt;
  param.reptCnt = kReptCnt;
  prodQuanObj.SetParam(param);

  // evaluate the time consumption under the single/multiple setting
  prodQuanObj.Fillup();
  swSngQury.Start();
  prodQuanObj.MsrSngTime();
  std::cout << "[INFO] PQ-single  : " << swSngQury.Stop() << " (s)\n";
  swMulQury.Start();
  prodQuanObj.MsrMulTime();
  std::cout << "[INFO] PQ-multiple: " << swMulQury.Stop() << " (s)\n";
}

int main(int argc, char* argv[]) {
  EvaProdQuan();

  return 0;
}


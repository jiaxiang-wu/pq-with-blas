/*
  File Name: Main.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 27 Jan 2016 07:55:01 PM CST
 */

#include <iostream>
#include <iomanip>

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
  float timeElpsSng;
  float timeElpsMul;

  // set-up PQ's parameters
  param.featCnt = kFeatCnt;
  param.scbkCnt = kScbkCnt;
  param.scwdCnt = kScwdCnt;
  param.quryCnt = kQuryCnt;
  param.reptCnt = kReptCnt;
  prodQuanObj.SetParam(param);
  prodQuanObj.Fillup();

  /* STAGE #1: built-in implementation */
  // evaluate the time consumption of processing a single query
  swSngQury.Start();
  prodQuanObj.MsrSngTime(false);
  timeElpsSng = swSngQury.Stop() / kReptCnt;

  // evaluate the time consumption of processing multiple queries
  swMulQury.Start();
  prodQuanObj.MsrMulTime(false);
  timeElpsMul = swMulQury.Stop() / kReptCnt;

  // display the comparison on time comsumption
  std::cout << std::fixed;
  std::cout << "[INFO] PQ-NoMKL-Single  : " << std::setprecision(3) \
      << timeElpsSng * 1000 << " ms\n";
  std::cout << "[INFO] PQ-NoMKL-Multiple: " << std::setprecision(3) \
      << timeElpsMul * 1000 << " ms\n";

  /* STAGE #2: MKL implementation */
  // evaluate the time consumption of processing a single query
  swSngQury.Start();
  prodQuanObj.MsrSngTime(true);
  timeElpsSng = swSngQury.Stop() / kReptCnt;

  // evaluate the time consumption of processing multiple queries
  swMulQury.Start();
  prodQuanObj.MsrMulTime(true);
  timeElpsMul = swMulQury.Stop() / kReptCnt;

  // display the comparison on time comsumption
  std::cout << std::fixed;
  std::cout << "[INFO] PQ-MKL-Single    : " << std::setprecision(3) \
      << timeElpsSng * 1000 << " ms\n";
  std::cout << "[INFO] PQ-MKL-Multiple  : " << std::setprecision(3) \
      << timeElpsMul * 1000 << " ms\n";
}

int main(int argc, char* argv[]) {
  EvaProdQuan();

  return 0;
}


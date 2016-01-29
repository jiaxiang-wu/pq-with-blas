/*
  File Name: Main.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 27 Jan 2016 07:55:01 PM CST
 */

#include <iostream>
#include <iomanip>

#include "ProdQuan.h"
#include "OptProdQuan.h"
#include "StopWatch.hpp"

// define constant variables
const std::size_t kFeatCnt = 128;
const std::size_t kScbkCnt = 8;
const std::size_t kScwdCnt = 256;
const std::size_t kQuryCnt = 64;
const std::size_t kReptCnt = 1000;
const std::size_t kFeatCntPrj = kFeatCnt;

// evaluation function for Product Quantization
void EvaProdQuan(void);
// evaluation function for Optimized Product Quantization
void EvaOptProdQuan(void);
// evaluation function for Composite Quantization
void EvaCompQuan(void);
// evaluation function for Sparse Composite Quantization
void EvaSprsCompQuan(void);
// evaluation function for Tree Quantization
void EvaTreeQuan(void);

// general evaluation function for all quantization methods
template<class GnrlQuan>
void EvaGnrlQuan(GnrlQuan& quanObj);

int main(int argc, char* argv[]) {
  EvaProdQuan();
  EvaOptProdQuan();

  return 0;
}

void EvaProdQuan(void) {
  // declare objects
  ProdQuan prodQuanObj;
  ProdQuanParam param;

  // set-up PQ's parameters
  param.featCnt = kFeatCnt;
  param.scbkCnt = kScbkCnt;
  param.scwdCnt = kScwdCnt;
  param.quryCnt = kQuryCnt;
  param.reptCnt = kReptCnt;
  prodQuanObj.SetParam(param);
  prodQuanObj.Fillup();

  // call the general evaluation function
  EvaGnrlQuan(prodQuanObj);
}

void EvaOptProdQuan(void) {
  // declare objects
  OptProdQuan optProdQuanObj;
  OptProdQuanParam param;

  // set-up OPQ's parameters
  param.featCnt = kFeatCnt;
  param.scbkCnt = kScbkCnt;
  param.scwdCnt = kScwdCnt;
  param.quryCnt = kQuryCnt;
  param.reptCnt = kReptCnt;
  param.featCntPrj = kFeatCntPrj;
  optProdQuanObj.SetParam(param);
  optProdQuanObj.Fillup();

  // call the general evaluation function
  EvaGnrlQuan(optProdQuanObj);
}

template<class GnrlQuan>
void EvaGnrlQuan(GnrlQuan& quanObj) {
  // declare variable for timing
  StopWatch swSngQury;
  StopWatch swMulQury;
  float timeElpsSng;
  float timeElpsMul;

  /* STAGE #1: built-in implementation */
  // evaluate the time consumption of processing a single query
  swSngQury.Start();
  quanObj.MsrSngTime(false);
  timeElpsSng = swSngQury.Stop() / kReptCnt;

  // evaluate the time consumption of processing multiple queries
  swMulQury.Start();
  quanObj.MsrMulTime(false);
  timeElpsMul = swMulQury.Stop() / kReptCnt;

  // display the comparison on time comsumption
  std::cout << std::fixed;
  std::cout << "[INFO] NoMKL-Single  : " << std::setprecision(3) \
      << timeElpsSng * 1000 << " ms\n";
  std::cout << "[INFO] NoMKL-Multiple: " << std::setprecision(3) \
      << timeElpsMul * 1000 << " ms\n";

  /* STAGE #2: MKL implementation */
  // evaluate the time consumption of processing a single query
  swSngQury.Start();
  quanObj.MsrSngTime(true);
  timeElpsSng = swSngQury.Stop() / kReptCnt;

  // evaluate the time consumption of processing multiple queries
  swMulQury.Start();
  quanObj.MsrMulTime(true);
  timeElpsMul = swMulQury.Stop() / kReptCnt;

  // display the comparison on time comsumption
  std::cout << std::fixed;
  std::cout << "[INFO] MKL-Single    : " << std::setprecision(3) \
      << timeElpsSng * 1000 << " ms\n";
  std::cout << "[INFO] MKL-Multiple  : " << std::setprecision(3) \
      << timeElpsMul * 1000 << " ms\n";
}


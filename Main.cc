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
#include "CompQuan.h"
#include "SprsCompQuan.h"

#include "StopWatch.hpp"

// define constant variables
const std::size_t kFeatCnt = 128;
const std::size_t kScbkCnt = 8;
const std::size_t kScwdCnt = 256;
const std::size_t kQuryCnt = 10000;
const std::size_t kBtchSiz = 50;
const std::size_t kFeatCntPrj = kFeatCnt;
const float kSprsRat = 1.0 / kScbkCnt; // to compare with PQ

// evaluation function for Product Quantization
void EvaProdQuan(const BaseQuanParam& bqParam);
// evaluation function for Optimized Product Quantization
void EvaOptProdQuan(const BaseQuanParam& bqParam);
// evaluation function for Composite Quantization
void EvaCompQuan(const BaseQuanParam& bqParam);
// evaluation function for Sparse Composite Quantization
void EvaSprsCompQuan(const BaseQuanParam& bqParam);
// evaluation function for Tree Quantization
void EvaTreeQuan(const BaseQuanParam& bqParam);

// general evaluation function for all quantization methods
template<class GnrlQuan>
void EvaGnrlQuan(GnrlQuan& quanObj);

int main(int argc, char* argv[]) {
  // define parameters for base quantization
  BaseQuanParam bqParam;
  bqParam.featCnt_ = kFeatCnt;
  bqParam.scbkCnt_ = kScbkCnt;
  bqParam.scwdCnt_ = kScwdCnt;
  bqParam.quryCnt_ = kQuryCnt;
  bqParam.btchSiz_ = kBtchSiz;

  // evaluate each quantization method
  EvaProdQuan(bqParam);
  EvaOptProdQuan(bqParam);
  EvaCompQuan(bqParam);
  EvaSprsCompQuan(bqParam);

  return 0;
}

void EvaProdQuan(const BaseQuanParam& bqParam) {
  // declare objects
  ProdQuan prodQuanObj;

  // set-up PQ's parameters
  ProdQuanParam param(bqParam);
  prodQuanObj.SetParam(param);
  prodQuanObj.Fillup();

  // call the general evaluation function
  EvaGnrlQuan(prodQuanObj);
}

void EvaOptProdQuan(const BaseQuanParam& bqParam) {
  // declare objects
  OptProdQuan optProdQuanObj;

  // set-up OPQ's parameters
  OptProdQuanParam param(bqParam);
  param.featCntPrj_ = kFeatCntPrj;
  optProdQuanObj.SetParam(param);
  optProdQuanObj.Fillup();

  // call the general evaluation function
  EvaGnrlQuan(optProdQuanObj);
}

void EvaCompQuan(const BaseQuanParam& bqParam) {
  // declare objects
  CompQuan compQuanObj;

  // set-up CQ's parameters
  CompQuanParam param(bqParam);
  compQuanObj.SetParam(param);
  compQuanObj.Fillup();

  // call the general evaluation function
  EvaGnrlQuan(compQuanObj);
}

void EvaSprsCompQuan(const BaseQuanParam& bqParam) {
  // declare objects
  SprsCompQuan sprsCompQuanObj;

  // set-up CQ's parameters
  SprsCompQuanParam param(bqParam, kSprsRat);
  sprsCompQuanObj.SetParam(param);
  sprsCompQuanObj.Fillup();

  // call the general evaluation function
  EvaGnrlQuan(sprsCompQuanObj);
}

template<class GnrlQuan>
void EvaGnrlQuan(GnrlQuan& quanObj) {
  // declare variable for timing
  StopWatch swSngQury;
  StopWatch swMulQury;
  float timeElpsSng;
  float timeElpsMul;

  // define the MKL usage indicators
  std::vector<bool> enblMklLst(2);
  enblMklLst[0] = false; // use built-in implementaion
  enblMklLst[1] = true; // use MKL implementation

  // evaluate the time consumption under two settings
  std::cout << std::fixed; // switch to fixed-point output
  for (std::size_t idx = 0; idx < enblMklLst.size(); ++idx) {
    // evaluate the time consumption of processing a single query
    swSngQury.Start();
    quanObj.MsrSngTime(enblMklLst[idx]);
    timeElpsSng = swSngQury.Stop() / kQuryCnt;

    // evaluate the time consumption of processing multiple queries
    swMulQury.Start();
    quanObj.MsrMulTime(enblMklLst[idx]);
    timeElpsMul = swMulQury.Stop() / kQuryCnt;

    // display the comparison on time comsumption
    std::cout << "[INFO] " << (enblMklLst[idx] ? \
        "use MKL implementation\n" : "use built-in implementation\n");
    std::cout << "[INFO] Single  : " << std::setprecision(3) \
        << timeElpsSng * 1000 << " ms\n";
    std::cout << "[INFO] Multiple: " << std::setprecision(3) \
        << timeElpsMul * 1000 << " ms\n";
  } // ENDFOR: idx
}


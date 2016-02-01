/*
  File Name: OptProdQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Fri 29 Jan 2016 04:20:47 PM CST
 */

#ifndef OPTPRODQUAN_H_INCLUDED
#define OPTPRODQUAN_H_INCLUDED

#include "BaseQuan.h"

class OptProdQuanParam : public BaseQuanParam {
public:
  OptProdQuanParam(void) {}
  OptProdQuanParam(const BaseQuanParam& param);

public:
  // the number of projected feature dimensions
  std::size_t featCntPrj_;
};

class OptProdQuan: public BaseQuan {
public:
  // set-up OPQ's parameters
  void SetParam(const OptProdQuanParam& param);
  // fill-up essential arrays with random number
  void Fillup(void);
  // measure the time consumption of processing a single query
  void MsrSngTime(const bool enblMKL);
  // measure the time consumption of processing multiple queries
  void MsrMulTime(const bool enblMKL);

public:
  // OPQ's parameters
  OptProdQuanParam param_;
  // the number of projected feature dimensions for each sub-codebook
  std::size_t featCntPrjPerScbk_;

private:
  // the projected query (single)
  ArraySiz quryPrjSngSiz_;
  Array<float> quryPrjSng_;
  // the projected queries (multiple)
  ArraySiz quryPrjMulSiz_;
  Array<float> quryPrjMul_;
  // the projection matrix
  ArraySiz matrPrjSiz_;
  Array<float> matrPrj_;
};

#endif // OPTPRODQUAN_H_INCLUDED


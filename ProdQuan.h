/*
  File Name: ProdQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 02:41:16 PM CST
 */

#ifndef PRODQUAN_H_INCLUDED
#define PRODQUAN_H_INCLUDED

#include "BaseQuan.h"

class ProdQuanParam : public BaseQuanParam {
public:
  ProdQuanParam(void) {}
  ProdQuanParam(const BaseQuanParam& param);

public:
  // no extra parameters required
};

class ProdQuan: public BaseQuan {
public:
  // set-up PQ's parameters
  void SetParam(const ProdQuanParam& param);
  // fill-up essential arrays with random number
  void Fillup(void);
  // measure the time consumption of processing a single query
  void MsrSngTime(const bool enblMKL);
  // measure the time consumption of processing multiple queries
  void MsrMulTime(const bool enblMKL);

private:
  // PQ's parameters
  ProdQuanParam param_;
  // the number of feature dimensions for each sub-codebook
  std::size_t featCntPerScbk_;
};

#endif // PRODQUAN_H_INCLUDED


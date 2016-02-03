/*
  File Name: SprsCompQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Wed 03 Feb 2016 02:56:19 PM CST
 */

#ifndef SPRSCOMPQUAN_H_INCLUDED
#define SPRSCOMPQUAN_H_INCLUDED

#include "BaseQuan.h"

class SprsCompQuanParam : public BaseQuanParam {
public:
  SprsCompQuanParam(void) {}
  SprsCompQuanParam(const BaseQuanParam& param);

public:
  // the sparsity ratio
  float sprsRat_;
};

class SprsCompQuan: public BaseQuan {
public:
  // set-up SCQ's parameters
  void SetParam(const CompQuanParam& param);
  // fill-up essential arrays with random number
  void Fillup(void);
  // measure the time consumption of processing a single query
  void MsrSngTime(const bool enblMKL);
  // measure the time consumption of processing multiple queries
  void MsrMulTime(const bool enblMKL);

private:
  // SCQ's parameters
  SprsCompQuanParam param_;
};

#define SPRSCOMPQUAN_H_INCLUDED


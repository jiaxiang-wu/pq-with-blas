/*
  File Name: CompQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Fri 29 Jan 2016 07:30:33 PM CST
 */

#ifndef COMPQUAN_H_INCLUDED
#define COMPQUAN_H_INCLUDED

#include "BaseQuan.h"

class CompQuanParam : public BaseQuanParam {
public:
  CompQuanParam(void) {}
  CompQuanParam(const BaseQuanParam& param);

public:
  // no extra parameters required
};

class CompQuan: public BaseQuan {
public:
  // set-up CQ's parameters
  void SetParam(const CompQuanParam& param);
  // fill-up essential arrays with random number
  void Fillup(void);
  // measure the time consumption of processing a single query
  void MsrSngTime(const bool enblMKL);
  // measure the time consumption of processing multiple queries
  void MsrMulTime(const bool enblMKL);

private:
  // CQ's parameters
  CompQuanParam param_;
};

#endif // COMPQUAN_H_INCLUDED


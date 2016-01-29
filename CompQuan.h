/*
  File Name: CompQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Fri 29 Jan 2016 07:30:33 PM CST
 */

#ifndef COMPQUAN_H_INCLUDED
#define COMPQUAN_H_INCLUDED

#include "BaseQuan.h"

typedef struct {
  std::size_t featCnt;
  std::size_t scbkCnt;
  std::size_t scwdCnt;
  std::size_t quryCnt;
  std::size_t reptCnt;
} CompQuanParam;

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
  // extra member variables
};

#endif // COMPQUAN_H_INCLUDED


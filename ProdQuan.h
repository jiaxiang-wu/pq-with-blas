/*
  File Name: ProdQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 02:41:16 PM CST
 */

#ifndef PRODQUAN_H_INCLUDED
#define PRODQUAN_H_INCLUDED

#include "BaseQuan.h"

typedef struct {
  std::size_t featCnt;
  std::size_t scbkCnt;
  std::size_t scwdCnt;
  std::size_t quryCnt;
  std::size_t reptCnt;
} ProdQuanParam;

class ProdQuan: public BaseQuan {
public:
  // set-up PQ's parameters
  void SetParam(const ProdQuanParam& param);

private:
  // extra member variables
};

#endif // PRODQUAN_H_INCLUDED


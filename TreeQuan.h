/*
  File Name: TreeQuan.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Mon 15 Feb 2016 02:44:55 PM CST
 */

#ifndef TREEQUAN_H_INCLUDED
#define TREEQUAN_H_INCLUDED

#include "BaseQuan.h"

class TreeQuanParam : public BaseQuanParam {
public:
  TreeQuanParam(void) {}
  TreeQuanParam(const BaseQuanParam& param);

public:
  // no extra parameters required
};

class DimConvParam {
public:
  // the index list of each feature dimension's sub-codebook
  std::vector<std::size_t> scbkIdxLst_;
  // the index list of each feature dimension's insertion position
  std::vector<std::size_t> instIdxLst_;
  // the length of each sub-codebook (number of feature dimensions)
  std::vector<std::size_t> scbkLenLst_;
};

class TreeQuan: public BaseQuan {
public:
  // set-up TQ's parameters
  void SetParam(const TreeQuanParam& param);
  // fill-up essential arrays with random number
  void Fillup(void);
  // measure the time consumption of processing a single query
  void MsrSngTime(const bool enblMKL);
  // measure the time consumption of processing multiple queries
  void MsrMulTime(const bool enblMKL);

private:
  // TQ's parameters
  TreeQuanParam param_;
  // the conversion parameter for DIM-SCBK
  DimConvParam dimConvParam_;
};

#endif // TREEQUAN_H_INCLUDED


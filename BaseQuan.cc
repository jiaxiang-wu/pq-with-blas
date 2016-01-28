/*
  File Name: BaseQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 03:28:28 PM CST
 */

#include "BaseQuan.h"

#include <cstdlib>
#include <cfloat>

void BaseQuan::FillArray(Array<float>& array) {
  float* p = array.GetDataPtr();
  std::size_t eleCnt = array.GetEleCnt();
  for (std::size_t eleIdx = 0; eleIdx < eleCnt; ++eleIdx) {
    p[eleIdx] = static_cast<float>(rand() % RAND_MAX) / (RAND_MAX - 1) - 0.5;
  }
}


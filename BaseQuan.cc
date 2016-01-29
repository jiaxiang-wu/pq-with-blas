/*
  File Name: BaseQuan.cc
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 03:28:28 PM CST
 */

#include "BaseQuan.h"

#include <cstdlib>
#include <cfloat>

void BaseQuan::AllctAndFill(const ArraySiz& siz, Array<float>& array) {
  // create a new array
  array.Create(siz);

  // fill-up the array with random numbers (-0.5 ~ +0.5)
  float* p = array.GetDataPtr();
  std::size_t eleCnt = array.GetEleCnt();
  for (std::size_t eleIdx = 0; eleIdx < eleCnt; ++eleIdx) {
    p[eleIdx] = static_cast<float>(rand() % RAND_MAX) / (RAND_MAX - 1) - 0.5;
  } // ENDFOR: eleIdx
}

void BaseQuan::AllctAndFill(const std::size_t len, 
    const ArraySiz& siz, std::vector<Array<float> >& arrays) {
  // create a list of arrays of the same size
  arrays.resize(len);
  for (std::size_t idx = 0; idx < len; ++idx) {
    AllctAndFill(siz, arrays[idx]);
  } // ENDFOR: idx
}


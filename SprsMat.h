/*
  File Name: SprsMat.h
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Mon 01 Feb 2016 11:05:53 AM CST
 */

#ifndef SPRSMAT_H_INCLUDED
#define SPRSMAT_H_INCLUDED

template<typename Dtype>
class SprsMat {
public:
  // generate a sparse matrix from a dense array
  void GnrtMat(const Array<Dtype>& array);
};

#endif // SPRSMAT_H_INCLUDED


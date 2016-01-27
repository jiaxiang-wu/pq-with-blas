#!/bin/bash
# FileName: ExtrPackages.sh
# Author: Jiaxiang Wu
# E-mail: jiaxiang.wu.90@gmail.com
# Created Time: Wed 27 Jan 2016 07:07:19 PM CST

# extract OpenBLAS
# URL: http://github.com/xianyi/OpenBLAS/archive/v0.2.15.tar.gz
savePath="./packages/OpenBLAS-0.2.15.tar.gz"
extrcDirDft="./OpenBLAS-0.2.15"
extrcDir="./OpenBLAS"
rm -rf ${extrcDirDft} ${extrcDir}
tar -xvf ${savePath}
mv ${extrcDirDft} ${extrcDir}

# extract SparseBLAS
# URL: http://math.nist.gov/spblas/nist_spblas_1_02.zip
savePath="./packages/SparseBLAS-1.02.zip"
extrcDir="./SparseBLAS"
rm -rf ${extrcDir}
mkdir -v ${extrcDir}
cd ${extrcDir}
unzip "../"${savePath}
cd ..


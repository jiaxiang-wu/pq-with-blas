#!/bin/bash
# FileName: MakeOpenBLAS.sh
# Author: Jiaxiang Wu
# E-mail: jiaxiang.wu.90@gmail.com
# Created Time: Wed 27 Jan 2016 05:04:53 PM CST

# set-up the directory path
codeDir="./OpenBLAS"
buldDir="./OpenBLAS-build"

# re-build OpenBLAS
rm -rf ${buldDir}
mkdir -v ${buldDir}
cd ${codeDir}
make -j8
make PREFIX="../"${buldDir} install
cd ..


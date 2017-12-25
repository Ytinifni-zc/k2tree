#!/bin/bash
CUR_DIR=`pwd`
OLD_DIR="$( cd "$( dirname "$0" )" && pwd )" # gets the directory where the script is located in
cd "${OLD_DIR}"

#cmake .. -DCMAKE_INSTALL_PREFIX=${HOME}/k2tree/K2Tree/thirdparty/libsdsl \
#    -DCMAKE_C_COMPILER=/home/zhaocheng/local/bin/clang \
#    -DCMAKE_CXX_COMPILER=/home/zhaocheng/local/bin/clang++ 
/home/zhaocheng/anaconda2/bin/cmake .. \
    -DCMAKE_C_COMPILER=/home/zhaocheng/local/bin/gcc \
    -DCMAKE_CXX_COMPILER=/home/zhaocheng/local/bin/g++ 
#    -DCMAKE_C_COMPILER=/usr/bin/gcc \
#    -DCMAKE_CXX_COMPILER=/usr/bin/g++ 
make -j
#make install

cd ${CUR_DIR}

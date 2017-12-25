/usr/bin/g++ -o test_rank ../tests/test_rank.cc  \
    lib/libasync++.a  lib/libdacs.a  lib/libgtest.a  lib/libk2tree.a  lib/libdivsufsort64.a  lib/libk2tree.a  \
    lib/libsdsl.a  lib/libdivsufsort.a   \
    -I../include \
    -I../thirdparty/asyncplusplus/include \
    -I../thirdparty/boost/include \
    -I../thirdparty/libsdsl/include \
    -I../thirdparty/dacs/include \
    -I../thirdparty/gtest/include  \
    -std=c++11 \
    -lpthread

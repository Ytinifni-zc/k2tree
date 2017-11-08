//
// Created by inFinity on 2017/11/7.
//

#include <gtest/gtest.h>
#include <k2tree.h>

using namespace k2tree;

//int main() {
TEST(Read, read2k2tree) {
    k2tree::k2tree kt(path);
    ASSERT_NE(kt.T().size(), 0);
    ASSERT_NE(kt.L().size(), 0);
    for (auto t : kt.T()) {
        cout << t.to_string() << " ";
    }
    cout << endl;
    for (auto l : kt.L()) {
        cout << l.to_string() << " ";
    }
    cout << endl;
}

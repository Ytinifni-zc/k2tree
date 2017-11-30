//
// Created by inFinity on 2017/11/27.
//

#include <gtest/gtest.h>
#include <k2tree.h>

using namespace libk2tree;
using namespace std;

TEST(Rank, test_tree) {
    const string path = "./k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);
    ASSERT_NE(kt.T().size(), 0);
    ASSERT_NE(kt.L().size(), 0);

    ASSERT_EQ(kt.rank(0), 1);
    ASSERT_EQ(kt.rank(2), 2);
    ASSERT_EQ(kt.rank(35), 17);
    ASSERT_EQ(kt.rank(40), 18);
}

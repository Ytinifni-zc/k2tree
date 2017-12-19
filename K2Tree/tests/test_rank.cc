//
// Created by inFinity on 2017/11/27.
//

#include <gtest/gtest.h>
#include <k2tree.h>
#include "tests_utils.h"

using namespace libk2tree;
using namespace std;

/*
TEST(Rank, test_tree) {
    const string path = "/home/zhaocheng/k2tree/K2Tree/_build/tests/k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);
    ASSERT_NE(kt.T().size(), 0);
    ASSERT_NE(kt.L().size(), 0);

    ASSERT_EQ(kt.rank(0), 1);
    ASSERT_EQ(kt.rank(2), 2);
    ASSERT_EQ(kt.rank(35), 17);
    ASSERT_EQ(kt.rank(40), 18);
}
*/

TEST(Rank, Benchmark) {
    shared_ptr<k2tree> kt;
    utils::cost([&](){
        kt = read_twitter();
    });

    auto rand_size = 100000;
    auto r100 = 100;
    vector<int> rand_100, rand_10000;
    utils::cost([&]() {
        std::cerr << "Generate rand node vector(100 and 10000). \t";
        rand_100.resize(r100);
        rand_10000.resize(rand_size);
        for (int i = 0; i < rand_size; ++i) {
          if(i < r100) rand_100[i] = std::rand() % TWITTER_NODE_NUM;
          rand_10000[i] = std::rand() % TWITTER_NODE_NUM;
        }
    });

    utils::cost([=]() {
        std::cerr << "Rank[" << rand_size << "] using: \t";
        for (auto _n: rand_10000)
            kt->rank(_n);
    });

}

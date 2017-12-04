//
// Created by inFinity on 2017/11/29.
//

#include <gtest/gtest.h>
#include "tests_utils.h"

using namespace libk2tree;
using namespace std;

TEST(CheckLink, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(1, 2));
    ASSERT_TRUE(kt.check_link(10, 7));
    ASSERT_TRUE(kt.check_link(11, 10));
    ASSERT_TRUE(kt.check_link(2, 5));
    ASSERT_FALSE(kt.check_link(10, 8));
    ASSERT_FALSE(kt.check_link(11, 1));
    ASSERT_FALSE(kt.check_link(13, 1));

}

TEST(CheckLink, test_csv_kl4) {

    const string path = "./k2tree/kl4/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(1, 2));
    ASSERT_TRUE(kt.check_link(10, 7));
    ASSERT_TRUE(kt.check_link(11, 10));
    ASSERT_TRUE(kt.check_link(2, 5));
    ASSERT_FALSE(kt.check_link(10, 8));
    ASSERT_FALSE(kt.check_link(11, 1));
    ASSERT_FALSE(kt.check_link(13, 1));
}

TEST(CheckLink, twitter0_kl4) {
    auto kL = 4;
    auto kt = read_twitter_partition(0, kL);

    ASSERT_TRUE(kt->check_link(4, 3));
    ASSERT_TRUE(kt->check_link(5, 2));
    ASSERT_FALSE(kt->check_link(5, 4));

    ASSERT_TRUE(kt->check_link(325396, 222193));
    ASSERT_TRUE(kt->check_link(325396, 325351));
    ASSERT_TRUE(kt->check_link(325397, 325351));

}

TEST(CheckLink, twitter0_kl8) {
    auto kL = 8;
    auto kt = read_twitter_partition(0, kL);

    ASSERT_TRUE(kt->check_link(4, 3));
    ASSERT_TRUE(kt->check_link(5, 2));
    ASSERT_FALSE(kt->check_link(5, 4));
    ASSERT_TRUE(kt->check_link(325396, 222193));
    ASSERT_TRUE(kt->check_link(325396, 325351));
    ASSERT_TRUE(kt->check_link(325397, 325351));

}

TEST(CheckLink, twitter0_kl16) {
    auto kL = 16;
    auto kt = read_twitter_partition(0, kL);

    ASSERT_TRUE(kt->check_link(4, 3));
    ASSERT_TRUE(kt->check_link(5, 2));
    ASSERT_FALSE(kt->check_link(5, 4));
    ASSERT_TRUE(kt->check_link(325396, 222193));
    ASSERT_TRUE(kt->check_link(325396, 325351));
    ASSERT_TRUE(kt->check_link(325397, 325351));

}

TEST(CheckLink, twitter8514_kl16) {
    auto kL = 16;
    auto kt = read_twitter_partition(8514, kL);

    ASSERT_TRUE(kt->check_link(1, 15));
    ASSERT_TRUE(kt->check_link(325409, 74107));
    ASSERT_TRUE(kt->check_link(325408, 142158));

}

TEST(CompressedCheckLink, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    k2tree_compressed kt(2, 2, 1, 2, node_num, path, libk2tree::read_T, true);

    ASSERT_TRUE(kt.check_link(1, 2));
    ASSERT_TRUE(kt.check_link(10, 7));
    ASSERT_TRUE(kt.check_link(11, 10));
    ASSERT_TRUE(kt.check_link(2, 5));
    ASSERT_FALSE(kt.check_link(10, 8));
    ASSERT_FALSE(kt.check_link(11, 1));
    ASSERT_FALSE(kt.check_link(13, 1));

}

TEST(CompressedCheckLink, twitter0_kl4) {
    auto kL = 4;
    auto kt = read_twitter_partition_compressed(0, kL);

    ASSERT_TRUE(kt->check_link(4, 3));
    ASSERT_TRUE(kt->check_link(5, 2));
    ASSERT_FALSE(kt->check_link(5, 4));
    ASSERT_TRUE(kt->check_link(325396, 222193));
    ASSERT_TRUE(kt->check_link(325396, 325351));
    ASSERT_TRUE(kt->check_link(325397, 325351));

}

TEST(CompressedCheckLink, twitter0_kl8) {
    auto kL = 8;
    auto kt = read_twitter_partition_compressed(0, kL);

    ASSERT_TRUE(kt->check_link(4, 3));
    ASSERT_TRUE(kt->check_link(5, 2));
    ASSERT_FALSE(kt->check_link(5, 4));
    ASSERT_TRUE(kt->check_link(325396, 222193));
    ASSERT_TRUE(kt->check_link(325396, 325351));
    ASSERT_TRUE(kt->check_link(325397, 325351));

}

TEST(CompressedCheckLink, twitter0_kl16) {
    auto kL = 16;
    auto kt = read_twitter_partition_compressed(0, kL);

    ASSERT_TRUE(kt->check_link(4, 3));
    ASSERT_TRUE(kt->check_link(5, 2));
    ASSERT_FALSE(kt->check_link(5, 4));
    ASSERT_TRUE(kt->check_link(325396, 222193));
    ASSERT_TRUE(kt->check_link(325396, 325351));
    ASSERT_TRUE(kt->check_link(325397, 325351));

}

TEST(CompressedCheckLink, twitter8514_kl16) {
    auto kL = 16;
    auto kt = read_twitter_partition_compressed(8514, kL);

    ASSERT_TRUE(kt->check_link(1, 15));
    ASSERT_TRUE(kt->check_link(325409, 74107));
    ASSERT_TRUE(kt->check_link(325408, 142158));

}

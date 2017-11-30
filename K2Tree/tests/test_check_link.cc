//
// Created by inFinity on 2017/11/29.
//

#include <gtest/gtest.h>
#include <k2tree.h>

using namespace libk2tree;

TEST(CheckLink, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(1, 2));
    //ASSERT_TRUE(kt.check_link(10, 7));
    //ASSERT_TRUE(kt.check_link(11, 10));
    //ASSERT_TRUE(kt.check_link(2, 5));
    //ASSERT_FALSE(kt.check_link(10, 8));
    //ASSERT_FALSE(kt.check_link(11, 1));
    //ASSERT_FALSE(kt.check_link(13, 1));
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
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl4/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));

}

TEST(CheckLink, twitter0_kl8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl8/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 8, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));

}
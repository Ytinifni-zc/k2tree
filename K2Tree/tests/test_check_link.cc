//
// Created by inFinity on 2017/11/29.
//

#include <gtest/gtest.h>
#include <k2tree.h>
#include <k2tree_compressed.h>

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
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl4/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));

    ASSERT_TRUE(kt.check_link(325396, 222193));
    ASSERT_TRUE(kt.check_link(325396, 325351));
    ASSERT_TRUE(kt.check_link(325397, 325351));

}

TEST(CheckLink, twitter0_kl8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl8/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 8, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));
    ASSERT_TRUE(kt.check_link(325396, 222193));
    ASSERT_TRUE(kt.check_link(325396, 325351));
    ASSERT_TRUE(kt.check_link(325397, 325351));

}

TEST(CheckLink, twitter0_kl16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl16/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 16, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));
    ASSERT_TRUE(kt.check_link(325396, 222193));
    ASSERT_TRUE(kt.check_link(325396, 325351));
    ASSERT_TRUE(kt.check_link(325397, 325351));

}

TEST(CheckLink, twitter8514_kl16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl16/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 16, node_num, path, libk2tree::read_T);

    ASSERT_TRUE(kt.check_link(1, 15));
    ASSERT_TRUE(kt.check_link(325409, 74107));
    ASSERT_TRUE(kt.check_link(325408, 142158));

}

void show(const k2tree_compressed &kt, int ws) {
    int length = (36>ws)?36:ws;
    for (int i = 0; i < length; ++i) {
        cout << kt.L()[i];
        if (0 == (i+1)%ws) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < length; ++i) {
        cout << kt.accessCompressL(i);
        if (0 == (i+1)%ws) cout << " ";
    }
    cout << endl;

    int err = 0;
    for (int i = 0; i < length; ++i) {
        if (kt.accessCompressL(i) != kt.L()[i])
            err++;
    }
    std::cout << err << std::endl;

}

TEST(CompressedCheckLink, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    k2tree_compressed kt(2, 2, 1, 2, node_num, path, libk2tree::read_T, true);

    show(kt, 4);

    ASSERT_TRUE(kt.check_link(1, 2));
    ASSERT_TRUE(kt.check_link(10, 7));
    ASSERT_TRUE(kt.check_link(11, 10));
    ASSERT_TRUE(kt.check_link(2, 5));
    ASSERT_FALSE(kt.check_link(10, 8));
    ASSERT_FALSE(kt.check_link(11, 1));
    ASSERT_FALSE(kt.check_link(13, 1));

}

TEST(CompressedCheckLink, twitter0_kl4) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl4/";
    const size_t node_num = 325409;

    k2tree_compressed kt(2, 2, 1, 4, node_num, path, libk2tree::read_T, true);
    show(kt, 4*4);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));
    ASSERT_TRUE(kt.check_link(325396, 222193));
    ASSERT_TRUE(kt.check_link(325396, 325351));
    ASSERT_TRUE(kt.check_link(325397, 325351));

}

TEST(CompressedCheckLink, twitter0_kl8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl8/";
    const size_t node_num = 325409;

    k2tree_compressed kt(2, 2, 1, 8, node_num, path, libk2tree::read_T, true);

    show(kt, 8*8);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));
    ASSERT_TRUE(kt.check_link(325396, 222193));
    ASSERT_TRUE(kt.check_link(325396, 325351));
    ASSERT_TRUE(kt.check_link(325397, 325351));

}

TEST(CompressedCheckLink, twitter0_kl16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl16/";
    const size_t node_num = 325409;

    k2tree_compressed kt(2, 2, 1, 16, node_num, path, libk2tree::read_T, true);
    show(kt, 16*16);

    ASSERT_TRUE(kt.check_link(4, 3));
    ASSERT_TRUE(kt.check_link(5, 2));
    ASSERT_FALSE(kt.check_link(5, 4));
    ASSERT_TRUE(kt.check_link(325396, 222193));
    ASSERT_TRUE(kt.check_link(325396, 325351));
    ASSERT_TRUE(kt.check_link(325397, 325351));

}

TEST(CompressedCheckLink, twitter8514_kl16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl16/";
    const size_t node_num = 325409;

    k2tree_compressed kt(2, 2, 1, 16, node_num, path, libk2tree::read_T, true);
    show(kt, 16*16);

    ASSERT_TRUE(kt.check_link(1, 15));
    ASSERT_TRUE(kt.check_link(325409, 74107));
    ASSERT_TRUE(kt.check_link(325408, 142158));

}

//
// Created by inFinity on 2017/11/7.
//

#include <gtest/gtest.h>
#include <k2tree.h>
#include <utils/bit_vector.h>
#include <utils/time.h>
#include <utils/time.cc>

using namespace libk2tree;
using namespace std;

//int main() {
TEST(Read, readT) {

    const string path = "./k2tree/";
    const string filename = "../test.csv";
    const size_t node_num = 11, edge_num = 12;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);
    ASSERT_NE(kt.T().size(), 0);
    ASSERT_NE(kt.L().size(), 0);
    cout << kt.T().size() << endl;
    for (int i = 0; i < kt.T().size(); ++i) {
        cout << kt.T()[i];
    }
    cout << endl;
    cout << kt.L().size() << endl;
    for (int i = 0; i < kt.L().size(); ++i) {
        cout << kt.L()[i];
    }
    cout << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);
}

TEST(Read, readTvector) {

    const string path = "../tools/k2tree/";
    const string filename = "../test.csv";
    const size_t node_num = 11, edge_num = 12;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path);
    ASSERT_NE(kt.T().size(), 0);
    ASSERT_NE(kt.L().size(), 0);
    cout << kt.T().size() << endl;
    for (int i = 0; i < kt.T().size(); ++i) {
        cout << kt.T()[i];
    }
    cout << endl;
    cout << kt.L().size() << endl;
    for (int i = 0; i < kt.L().size(); ++i) {
        cout << kt.L()[i];
    }
    cout << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}

TEST(ReadTwitter0, readT_kL4) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl4/";
    const size_t node_num = 325409, edge_num = 578757;

    libk2tree::k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);
    cout << kt.T().size() << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}

TEST(ReadTwitter0, readT_kL8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl8/";
    const size_t node_num = 325409, edge_num = 578757;

    libk2tree::k2tree kt(2, 2, 1, 8, node_num, path, libk2tree::read_T);
    cout << kt.T().size() << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}

TEST(ReadTwitter8514, readT_kL4) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl4/";
    const size_t node_num = 325409, edge_num = 215287671;

    libk2tree::k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);
    cout << kt.T().size() << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}

TEST(ReadTwitter8514, readT_kL8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl8/";
    const size_t node_num = 325409, edge_num = 215287671;

    libk2tree::k2tree kt(2, 2, 1, 8, node_num, path, libk2tree::read_T);
    cout << kt.T().size() << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}

TEST(ReadTwitter8514, readT_kL16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl16/";
    const size_t node_num = 325409, edge_num = 215287671;

    libk2tree::k2tree kt(2, 2, 1, 16, node_num, path, libk2tree::read_T);
    cout << kt.T().size() << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}

/*

TEST(ReadTwitter, readT_kL8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/k2tree/kl8/";
    const size_t node_num = 41652230, edge_num = 1468365182;

    libk2tree::k2tree kt(2, 2, 1, 8, node_num, path, libk2tree::read_T);
    cout << kt.T().size() << endl;
    ASSERT_EQ(kt.edge_num(), edge_num);

}
 */
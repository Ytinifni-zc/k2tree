//
// Created by inFinity on 2017/11/30.
//

#include <gtest/gtest.h>
#include <k2tree.h>

using namespace libk2tree;
using namespace std;

void show_children(const vector<size_t> &children) {
    for (auto child : children) {
        cout << child << " ";
    }
    cout << endl;
}

TEST(GetChild, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(9));

}

TEST(GetChild, test_csv_kl4) {

    const string path = "./k2tree/kl4/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(10));
}

TEST(GetChild, twitter0_kl4) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl4/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(27));

}

TEST(GetChild, twitter0_kl8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl8/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 8, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(27));
}

TEST(GetChild, twitter0_kl16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl16/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 16, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(27));
}

TEST(GetChild, twitter8514_kl16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl16/";
    const size_t node_num = 325409;

    k2tree kt(2, 2, 1, 16, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(325409));

}

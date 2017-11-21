//
// Created by inFinity on 2017/11/17.
//

#include <gtest/gtest.h>
#include <k2tree_partition.h>
#include "../tools/config.h"

TEST(partition_k2tree, build) {
    int k0 = 128;
    libk2tree::k2tree_partition tree(k0, 2, 2, 1, 4, TWITTER_NODE_NUM, TWITTER_EDGE_NUM);

    string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/";
    vector<string> file_list(k0*k0);
    for (int i = 0; i < k0*k0; ++i) {
        file_list[i] = path + "twitter" + std::to_string(i) + ".csv";
    }
    string store_path = path + "k2tree/";

    tree.build_partition_k2tree(file_list, store_path);
}

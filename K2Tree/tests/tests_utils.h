//
// Created by inFinity on 2017/12/4.
//

#ifndef K2TREE_TESTS_UTILS_H
#define K2TREE_TESTS_UTILS_H

#include <k2tree_compressed.h>

using namespace libk2tree;

shared_ptr<k2tree> read_twitter_partition(const int part_num, const int kL) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter"
                        +std::to_string(part_num)+".tree/kl"
                        +std::to_string(kL)+"/";
    const size_t node_num = 325409;

    shared_ptr<k2tree> kt =
            std::make_shared<k2tree>(2, 2, 1, kL, node_num, path, libk2tree::read_T);
    return kt;

}

shared_ptr<k2tree_compressed> read_twitter_partition_compressed(const int part_num, const int kL) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter"
                        +std::to_string(part_num)+".tree/kl"
                        +std::to_string(kL)+"/";
    const size_t node_num = 325409;

    shared_ptr<k2tree_compressed> kt =
            std::make_shared<k2tree_compressed>(2, 2, 1, kL, node_num, path, libk2tree::read_T, true);
    return kt;

}


#endif //K2TREE_TESTS_UTILS_H

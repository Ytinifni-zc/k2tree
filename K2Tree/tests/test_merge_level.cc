//
// Created by zhaocheng on 17-11-19.
//

#include <gtest/gtest.h>
#include <k2tree.h>
#include "../tools/config.h"

TEST(merge, merge_test) {
    const string path = TEST_PATH;
    const string filename = TEST_PATH+"../../test.csv";
    const size_t n = TEST_NODE_NUM;
    const size_t m = TEST_EDGE_NUM;

    libk2tree::k2tree kt(2, 2, 1, 2, n, m);
    kt.build_from_edge_array_csv(filename, path, libk2tree::to_memory);
    kt.merge_tree_bitmap();
    sdsl::store_to_file(kt.L(), path+"L.bin");
    sdsl::store_to_file(kt.T(), path+"T.bin");
}

TEST(merge, merge_part0) {
    const string path = TWITTER_PATH+"../k2tree_partition/twitter0.k2tree/";
    const string filename = path+"../twitter0.csv";
    const size_t n = 325409;
    const size_t m = 578757;

    libk2tree::k2tree kt(2, 2, 1, 4, n, m);
    kt.build_from_edge_array_csv(filename, path, libk2tree::to_memory);
    kt.merge_tree_bitmap();
    sdsl::store_to_file(kt.L(), path+"L.bin");
    sdsl::store_to_file(kt.T(), path+"T.bin");
}

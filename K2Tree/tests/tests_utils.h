//
// Created by inFinity on 2017/12/4.
//

#ifndef K2TREE_TESTS_UTILS_H
#define K2TREE_TESTS_UTILS_H

#include <k2tree_compressed.h>
#include <utils/time.h>
#include <utils/time.cc>
#include "../tools/config.h"

using namespace libk2tree;

const uint64_t TWITTER_P_NODE_NUM = 325409;
const uint64_t TWITTER_P0_EDGE_NUM = 578756;
//const uint64_t TWITTER_P8514_EDGE_NUM = 325409;

shared_ptr<k2tree> read_data(const string &path, const size_t &node_num, const size_t &edge_num) {
    sdsl::bit_vector t, l;

    utils::cost([&](){
        std::cerr << "Load from file: ";
        sdsl::load_from_file(t, path+"T.bin");
        sdsl::load_from_file(l, path+"L.bin");
        //sdsl::load_from_file(t, path+"pT0.bin");
        //sdsl::load_from_file(l, path+"pL0.bin");
    });

    shared_ptr<k2tree> kt = std::make_shared<k2tree>(8, 8, 1, 8, node_num, edge_num, t, l);
    utils::cost([&](){
        std::cerr << "Build rank support: ";
        kt->build_rank_support();
        kt->split_T();
    });
    return kt;
}

shared_ptr<k2tree> read_twitter() {
    const string path = TWITTER_PATH;
    const size_t node_num = TWITTER_NODE_NUM;
    const size_t edge_num = TWITTER_EDGE_NUM;
    return read_data(path, node_num, edge_num);
}

shared_ptr<k2tree> read_indochina() {
    const string path = INDOCHINA_PATH;
    const size_t node_num = INDOCHINA_NODE_NUM;
    const size_t edge_num = INDOCHINA_EDGE_NUM;
    return read_data(path, node_num, edge_num);

}

shared_ptr<k2tree> read_twitter_p0() {
    const string path = TWITTER_PATH + "../k2tree_partition/twitter0.tree/k_8_8_1_kl8/";
    const size_t node_num = TWITTER_P_NODE_NUM;
    const size_t edge_num = TWITTER_P0_EDGE_NUM;
    return read_data(path, node_num, edge_num);
}

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

//
// Created by inFinity on 2017/12/4.
//

#ifndef K2TREE_TESTS_UTILS_H
#define K2TREE_TESTS_UTILS_H

#include <k2tree_compressed.h>
#include <k2tree_partition.h>
#include <unordered_map>
#include <utils/time.h>
#include <utils/time.cc>
#include "../tools/config.h"

using namespace libk2tree;
using ::std::unordered_map;

const uint64_t TWITTER_P_NODE_NUM = 325409;
const uint64_t TWITTER_P0_EDGE_NUM = 578756;
//const uint64_t TWITTER_P8514_EDGE_NUM = 325409;

shared_ptr<k2tree> read_data(const string &path, const size_t &node_num, const size_t &edge_num,
        int k1, int k2, int k1_levels, int kL) {
    sdsl::bit_vector t, l;

    utils::cost([&](){
        std::cerr << "Load from file: ";
        sdsl::load_from_file(t, path+"T.bin");
        sdsl::load_from_file(l, path+"L.bin");
        //sdsl::load_from_file(t, path+"pT0.bin");
        //sdsl::load_from_file(l, path+"pL0.bin");
    });

    shared_ptr<k2tree> kt = std::make_shared<k2tree>(k1, k2, k1_levels, kL,
            node_num, edge_num, t, l);
    utils::cost([&](){
        std::cerr << "Build rank support: ";
        kt->build_rank_support();
        kt->split_T();
    });
    return kt;
}

shared_ptr<k2tree> read_twitter(int k1=8, int k2=8, int k1_levels=1, int kL=8) {
    const string path = TWITTER_PATH;
    const size_t node_num = TWITTER_NODE_NUM;
    const size_t edge_num = TWITTER_EDGE_NUM;
    return read_data(path, node_num, edge_num, k1, k2, k1_levels, kL);
}

shared_ptr<k2tree> read_indochina(int k1=8, int k2=8, int k1_levels=1, int kL=8) {
    const string path = INDOCHINA_PATH;
    const size_t node_num = INDOCHINA_NODE_NUM;
    const size_t edge_num = INDOCHINA_EDGE_NUM;
    return read_data(path, node_num, edge_num, k1, k2, k1_levels, kL);

}

shared_ptr<k2tree> read_twitter_p0(int k1=8, int k2=8, int k1_levels=1, int kL=8) {
    const string path = TWITTER_PATH + "../k2tree_partition/twitter0.tree/k_8_8_1_kl8/";
    const size_t node_num = TWITTER_P_NODE_NUM;
    const size_t edge_num = TWITTER_P0_EDGE_NUM;
    return read_data(path, node_num, edge_num, k1, k2, k1_levels, kL);
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

int test_graph_edges[12][2] = {
    {1, 2},
    {2, 3},
    {2, 4},
    {2, 5},
    {8, 7},
    {9, 7},
    {9, 10},
    {10, 7},
    {10, 9},
    {10, 11},
    {11, 7},
    {11, 10},
};

shared_ptr<k2tree> read_test_graph(int k1=2, int k2=2, int k1_levels=1, int kL=2) {
    const int node_num = 11;
    const int edge_num = 12;
    shared_ptr<k2tree> tree = std::make_shared<k2tree>(k1, k2, k1_levels, kL, node_num, edge_num);
    tree->build_from_edge_array_csv(test_graph_edges, edge_num);
    return tree;
}

shared_ptr<k2tree_edge_partition> read_k2tree_partition(const string &path=TWITTER_PARTITION_PATH) {
    return std::make_shared<k2tree_edge_partition>(path);
}

// K-V: <length of successor list, node list>
typedef unordered_map<int, vector<int>> node_bucket;
const string node_bucket_path = TWITTER_PATH + "../succs/";

shared_ptr<node_bucket> read_node_bucket(const string &path=node_bucket_path) {
    auto ret = std::make_shared<node_bucket>();
    vector<int> lengths = {1, 2, 3, 4, 5, 10, 30, 100, 1000, 10000};
    for (auto l: lengths){
        string filename = path+"succs"+std::to_string(l)+".txt";
        vector<int> v;
        ifstream in(filename, std::ios::in);
        for(;!in.eof();) {
            int n = 0;
            in >> n;
            v.push_back(n);
        }
        in.close();
        ret->insert({l, v});
    }
    return ret;
}

shared_ptr<k2tree> build_k2tree_from_edge_array(const string &dataset, const int &k1=8,
        const int &k2=8, const int &k1_levels=1, const int &kL=8) {
    assert(dataset=="twitter" || dataset=="indochina");

    int node_num = INDOCHINA_NODE_NUM, edge_num = INDOCHINA_EDGE_NUM;
    string filename = INDOCHINA_PATH + "../indochina-2004.bin";
    string save_t = INDOCHINA_PATH, save_l = INDOCHINA_PATH;
    if (dataset == "twitter") {
        node_num = TWITTER_NODE_NUM, edge_num = TWITTER_EDGE_NUM;
        filename = TWITTER_PATH + "../twitter-2010-2.bin";
        save_t = TWITTER_PATH;
        save_l = TWITTER_PATH;
    }
    save_t += std::to_string(k1) + std::to_string(k2) + std::to_string(kL) + ".bin";
    save_l += std::to_string(k1) + std::to_string(k2) + std::to_string(kL) + ".bin";
    int (*data)[2];
    long cnt;
    utils::cost([&](){
        std::cerr << "Load edge array from bin: ";
        std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
        long fileSize = in.tellg();
        int fd = open(filename.c_str(), O_RDONLY, 0);
        if (fd == -1) {
            perror("open failed.");
            exit(1);
        }
        void* ptr = mmap(0, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
        if (ptr == MAP_FAILED) {
            perror("mmap failed.");
            exit(1);
        }
        data = static_cast<int(*)[2]>(ptr);

        cnt = fileSize / 8;
        close(fd);
        in.close();
    });
    auto ret = std::make_shared<k2tree>(k1, k2, k1_levels, kL, node_num, edge_num);
    ret->build_from_edge_array_csv(data, cnt);
    utils::cost([&](){
        std::cerr << "Store to file." << std::endl;
        sdsl::store_to_file(ret->T(), save_t);
        sdsl::store_to_file(ret->L(), save_l);
    });
    return ret;
}

#endif //K2TREE_TESTS_UTILS_H

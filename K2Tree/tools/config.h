//
// Created by inFinity on 2017/11/16.
//

#ifndef K2TREE_CONFIG_H
#define K2TREE_CONFIG_H

#include <string>
#include <cstdlib>
#include <tuple>
#include <iostream>
#include <gflags/gflags.h>

using ::std::string;
using ::std::tuple;
using ::std::cout;
using ::std::endl;

const string TEST_PATH = "./k2tree/";
const string TEST_FILE = TEST_PATH + "../test.csv";
const size_t TEST_NODE_NUM = 11;
const size_t TEST_EDGE_NUM = 12;

const string TWITTER_PATH = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree/";
const string TWITTER_FILE = TWITTER_PATH + "../twitter-2010.csv";
const size_t TWITTER_NODE_NUM = 41652230;
const size_t TWITTER_EDGE_NUM = 1468365182;
const string TWITTER_PARTITION_PATH = TWITTER_PATH + "../partition/k2tree/";

const string INDOCHINA_PATH = "/mnt/disk1/zhaocheng/dataset/indochina-2004/k2tree/";
const string INDOCHINA_FILE = TWITTER_PATH + "../indochina-2004.csv";
const size_t INDOCHINA_NODE_NUM = 7414866;
const size_t INDOCHINA_EDGE_NUM = 194109311;



tuple<string, string, size_t, size_t, int, int, int, int> get_args(int argc, char** argv) {
    int flag = 1;
    int swh = 0;
    if (argc > 1) {
        flag = 0;
        swh = atoi(argv[1]);
    }
    string path;
    string filename;
    size_t node_num, edge_num;
    int k1, k2, k1_levels, kL;
    if (flag || swh == 1) {

        path = TEST_PATH;
        filename = TEST_FILE;
        node_num = TEST_NODE_NUM, edge_num = TEST_EDGE_NUM;

        if (!swh) {
            k1 = 2;
            k2 = 2;
            k1_levels = 1;
            kL = 2;
        } else {
            k1 = atoi(argv[2-flag]);
            k2 = atoi(argv[3-flag]);
            k1_levels = atoi(argv[4-flag]);
            kL = atoi(argv[5-flag]);
        }
    } else if (swh == 2) {
        path = TWITTER_PATH;
        filename = TWITTER_FILE;
        node_num = TWITTER_NODE_NUM, edge_num = TWITTER_EDGE_NUM;
        k1 = atoi(argv[2]);
        k2 = atoi(argv[3]);
        k1_levels = atoi(argv[4]);
        kL = atoi(argv[5]);
    } else {
        if (argc != 10) {
            std::cout << "|swh|path|filename|node num|edge num|k1|k2|k1_levels|kL|" << std::endl;
        } else {
            path = string(argv[2]);
            filename = string(argv[3]);
            node_num = atoi(argv[4]);
            edge_num = atoi(argv[5]);
            k1 = atoi(argv[6]);
            k2 = atoi(argv[7]);
            k1_levels = atoi(argv[8]);
            kL = atoi(argv[9]);
        }
    }

    return std::make_tuple(path, filename, node_num, edge_num, k1, k2, k1_levels, kL);

};

#endif //K2TREE_CONFIG_H

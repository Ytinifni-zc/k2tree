//
// Created by inFinity on 2017/11/14.
//
#include <k2tree.h>
#include <cstdlib>
#include <utils/time.h>
#include <iostream>
#include <utils/time.cc>

int main(int argc, char** argv) {
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

        path = "./k2tree/";
        filename = path + "../test.csv";
        node_num = 11, edge_num = 12;

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
        path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree/";
        filename = path + "../twitter-2010.csv";
        node_num = 41652230, edge_num = 1468365182;
        k1 = atoi(argv[2]);
        k2 = atoi(argv[3]);
        k1_levels = atoi(argv[4]);
        kL = atoi(argv[5]);
    } else {
        if (argc != 9) {
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

    auto read_bin = [=]() {
        k2tree::k2tree kt(k1, k2, k1_levels, kL, node_num, edge_num, path);
        std::cout << kt.T().size() << std::endl;
        for (int i = 0; i < kt.T().size(); ++i) {
            std::cout << kt.T()[i];
        }
        std::cout << std::endl;
        std::cout << kt.L().size() << std::endl;
        for (int i = 0; i < kt.L().size(); ++i) {
            std::cout << kt.L()[i];
        }
        std::cout << std::endl;
    };
    k2tree::utils::cost(read_bin);
    return 0;

}

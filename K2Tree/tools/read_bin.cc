//
// Created by inFinity on 2017/11/14.
//
#include <k2tree.h>
#include <cstdlib>
#include <utils/time.h>
#include <iostream>
#include <utils/time.cc>
#include "config.h"

int main(int argc, char** argv) {

    string path;
    string filename;
    size_t node_num, edge_num;
    int k1, k2, k1_levels, kL;

    std::tie(path, filename, node_num, edge_num, k1, k2, k1_levels, kL) = get_args(argc, argv);

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

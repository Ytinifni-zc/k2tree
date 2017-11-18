//
// Created by inFinity on 2017/11/7.
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

    auto build_tree = [=]() {
        libk2tree::k2tree tree(k1, k2, k1_levels, kL, node_num, edge_num);
        tree.build_from_edge_array_csv(filename, path, libk2tree::to_binary);
    };
    libk2tree::utils::cost(build_tree);
    return 0;

}
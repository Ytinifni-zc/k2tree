//
// Created by inFinity on 2017/11/7.
//

#ifndef K2TREE_BUILD_TREE_H
#define K2TREE_BUILD_TREE_H

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <base.h>

using std::ifstream;
using std::ofstream;
using std::unordered_map;
using std::unordered_set;
using std::map;
using std::cout;
using std::endl;
using std::pair;

using namespace k2tree;

inline int get_submat_size(const size_t &k) {
    return (int)ceil(((double)(k))/8);
}

typedef unordered_map<submat_pos, leaf_bits> leaves;
typedef unordered_map<submat_pos, submat> in_nodes;

struct submat_info {
    submat_pos u;
    submat_pos v;
    submat_info(int u, int v) : u(u), v(v) {}
};
bool operator==(const submat_info &si1, const submat_info &si2) {
    return si1.u == si2.u && si1.v == si2.v;
}
struct submat_info_hash {
    size_t operator()(const submat_info& si) const {
        std::hash<submat_pos> hash_fn;
        return hash_fn(si.u << 11) ^ hash_fn(si.v);
    }
};

// 上一层中不为0的子阵对应的u,v
typedef unordered_set<submat_info, submat_info_hash> level_1s;

struct pos_info {
    submat_info si;
    submat_pos level;
    pos_info(int u, int v, int l) : si(u, v), level(l) {}
};
bool operator==(const pos_info &pi1, const pos_info &pi2) {
    return pi1.si==pi2.si && pi1.level == pi2.level;
}
struct pos_info_hash {
    size_t operator()(const pos_info& pi) const {
        std::hash<submat_pos> hash_fn;
        return hash_fn(pi.si.u << 11) ^ hash_fn(pi.si.v) ^ hash_fn(pi.level<<17);
    }
};

/*
const string path = "/mnt/disk1/zhaocheng/dataset/enron/k2tree/";
const string filename = path + "../enron.nohead.csv";
const size_t node_num = 69244, edge_num = 276143;
 */
    const string path = "./k2tree/";
//const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree/";
    const string filename = path + "../test.csv";
//const string filename = path + "../twitter-2010.csv";
    const size_t node_num = 11, edge_num = 11;
//const size_t node_num = 41652230, edge_num = 1468365182;

#endif //K2TREE_BUILD_TREE_H

#ifndef TESTS_BUILD_TREE_H_
#define TESTS_BUILD_TREE_H_

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <bitset>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <cassert>

using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::map;
using std::bitset;
using std::vector;
using std::cout;
using std::endl;
using std::pair;

inline int get_submat_size(const size_t &k) {
    return (int)ceil(((double)(k))/8);
}

const size_t k = 2;
const size_t kL = 2;
const int level = 3;
const vector<int> k_level = {2, 2, 2, 2};

typedef bitset<26> submat_pos;
typedef bitset<kL*kL> leaf_bits;
typedef bitset<k*k> submat;
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


#endif
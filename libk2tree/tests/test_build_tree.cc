#include <gtest/gtest.h>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cassert>

using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::map;
using std::bitset;
using std::vector;

const size_t k = 2;
const size_t kL = 8;
typedef bitset<kL*kL> leaf_bits;
typedef bitset<k*k> submat;
typedef unordered_map<int, leaf_bits> leaves;
typedef unordered_map<int, submat> in_nodes;
typedef unordered_set<int> level_1s;

template<class T>
void hm_insert_bit(unordered_map<int, T> &hm, const size_t &n, const int &k, const int &u, const int &v) {
    int pos = (u/k)*(n/k) + v/k;
    T onehot = T(1)<<((u%k)*k + v%k);

    if (hm.find(pos) == hm.end())
        hm.insert(std::make_pair(pos, onehot));
    else 
        hm[pos] |= onehot;
}

template<class T>
void write_to_bin(unordered_map<int, T> hm, const string& filename, level_1s &last_level) {
    map<int, T> _hm(hm.begin(), hm.end());
    printf("Map converted.");

    ofstream out(filename, ofstream::binary);

    for (auto p: _hm) {
        int size = (int)ceil(((double)(p.second.size()))/8);
        out.write((char*) &p.second, size);
    }
    out.close();
}

void build_last_level_from_csv(const string& filename, const size_t & node_num, const size_t & edge_num, string path, level_1s &last_level) {
    // TODO 
    // 先把T、L写文件
    //const size_t bits = (size_t) ceil(log2(node_num));
    //typedef bitset<bits> leaf;
    //const int leaf_size = (int)ceil(((double)bits)/8);
    //const int leaf_bits_size = (int)ceil(((double)(kL*kL))/8);
    leaves last_hm;

    ifstream in(filename, ifstream::in);
    assert(in.fail() == false);
    int u = 0, v = 0;
    int pos = 0;
    leaf_bits onehot = 0;
    size_t n_prime = (size_t) ceil((double)node_num/kL)*kL;
    double line_num = 0;

    while (line_num <= edge_num) {

        in >> u >> v;
        u --;
        v --;

        hm_insert_bit<leaf_bits>(last_hm, n_prime, kL, u, v); 
        if (!((size_t)line_num % 1000000)) {
            fprintf(stderr, "<%d, %d>\n", u, v);
            fprintf(stderr, "%.2f\%\n", line_num/edge_num*100);
        }
        line_num++;

    }

    in.close();
    
    string l_filename = path + "L" + std::to_string(kL) + ".bin";
    printf("%s\n", l_filename.c_str());
    write_to_bin<leaf_bits>(last_hm, l_filename, last_level);
}

void build_internal(const size_t & node_num, string path, level_1s &last_level) {
    
    size_t current_level = (size_t)ceil(log(node_num/kL)/log(k));
    //int current_k = k;

    // Internal submatrix size = k*k.
    in_nodes t_hm;
    size_t current_pos = 0;
    submat current_onehot;
    int u = 0, v = 0;
    int pos = 0;
    leaf_bits onehot = 0;
    size_t n_prime = (size_t) ceil((double)node_num/kL)*kL;

    while (current_level) {
        printf("Current_level: %d\n", current_level);

        n_prime = ceil((double)n_prime/k)*k;

        for (auto last_pos : last_level) {
            u = last_pos/n_prime;
            v = last_pos%n_prime;

            hm_insert_bit<submat>(t_hm, n_prime, k, u, v);
        }

        last_level.clear();

        string t_filename = path + "T" + std::to_string(current_level) + ".bin";
        write_to_bin<submat>(t_hm, t_filename, last_level);
        t_hm.clear();

        current_level --;
    }

}

TEST(Build, test1) {

    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/";
    const string filename = path + "twitter-2010.csv";
    const size_t node_num = 41652230, edge_num = 1468365182;

    level_1s last_level;
    build_last_level_from_csv(filename, node_num, edge_num, path+"k2tree/", last_level);
    ASSERT_NE(last_level.size(), 0);
    //build_internal(node_num, path, last_level);
}
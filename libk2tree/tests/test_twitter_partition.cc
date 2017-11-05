#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <k2tree.h>
#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include <map>
#include <time.h>

#include <chrono>
#include <thread>

using ::libk2tree::K2TreeBuilder;
using ::libk2tree::HybridK2Tree;
using ::libk2tree::CompressedHybrid;
using ::libk2tree::K2TreePartitionBuilder;
using ::libk2tree::utils::Ceil;
using ::libk2tree::K2TreePartition;
using ::libk2tree::CompressedPartition;
using ::boost::filesystem::remove;
using ::std::ifstream;
using ::std::ofstream;
using ::std::string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::cout;
using ::std::endl;
using ::std::map;
using ::std::unordered_map;
using ::std::bitset;

const size_t kL = 8;
const size_t node_num = 41652230, edge_num = 1468365182;

const size_t bits = (size_t) ceil(log2(node_num));
typedef bitset<bits> leaf;
typedef bitset<kL*kL> leaf_bits;
unordered_map<leaf, leaf_bits> hm;

const int leaf_size = (int)ceil(((double)bits)/8);
const int leaf_bits_size = (int)ceil(((double)(kL*kL))/8);

    struct cmp_by_leaf {
        bool operator() (const leaf &k1, const leaf &k2) {
            return k1.to_ulong() < k2.to_ulong();
        }
    };

TEST(Twitter, last_level) {

    const string filename = "/mnt/disk1/zhaocheng/dataset/twitter-2010/twitter-2010.csv";

    ifstream in(filename, ifstream::in);
    assert(in.fail() == false);

    size_t u = 0, v = 0;
    double line_num = 0;
    leaf pos = 0;
    leaf_bits onehot = 0;
    size_t n_prime = 41652232;

    while (line_num <= edge_num) {

        in >> u >> v;
        u -= 1;
        v -= 1;

        pos = leaf((u/kL)*(n_prime/kL) + v/kL);
        onehot = leaf_bits(0x1ull << ((u%kL)*kL + v%kL));

        if (hm.find(pos) == hm.end())
            hm.insert(std::make_pair(pos, onehot));
        else
            hm[pos] |= onehot;

        if (!((size_t)line_num % 1000000)) {
            fprintf(stderr, "<%d, %d>\n", u, v);
            fprintf(stderr, "%.2f\%\n", line_num/edge_num*100);
        }

        ++line_num;
    }
    in.close();


}

/*
TEST(Twitter, write_hm2file) {
    const string filename = "tw_lastlevel.bin";
    ofstream out(filename, ofstream::binary);
    leaf k;
    leaf_bits v;
    for (auto it : hm) {

        k = it.first;
        v = it.second;
        out.write((char*)&k, leaf_size);
        out.write((char*)&v, leaf_bits_size);

    }
    out.close();
}
*/

TEST(Twitter, read_file2hm) {
    unordered_map<leaf, leaf_bits> newhm;
    const string filename = "tw_lastlevel.bin";
    ifstream fin(filename, ifstream::binary);
    leaf k;
    leaf_bits v;
    for (;!fin.eof();) {
        fin.read((char*)&k, leaf_size);
        fin.read((char*)&v, leaf_bits_size);
        newhm.insert(std::make_pair(k, v));
        //hm.insert(std::make_pair(k, v));
    }
    fin.close();
    ASSERT_EQ(hm, newhm);
    
    auto start = std::chrono::system_clock::now();
    map<leaf, leaf_bits, cmp_by_leaf> m1(newhm.begin(), newhm.end());
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    cout << "m1 constructor cost: " << double(duration.count()*std::chrono::microseconds::period::num/std::chrono::microseconds::period::den) << "s" << endl;

    ASSERT_TRUE(m1.size() > 0);
    start = std::chrono::system_clock::now();
    map<leaf, leaf_bits, cmp_by_leaf> m2(hm.begin(), hm.end());
    end = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    cout << "m2 constructor cost: " << double(duration.count()*std::chrono::microseconds::period::num/std::chrono::microseconds::period::den) << "s" << endl;

    ASSERT_EQ(m1, m2);
}

/*
TEST(Twitter, read_file2m) {

    map<leaf, leaf_bits, cmp_by_leaf> newhm;
    const string filename = "tw_lastlevel.bin";
    ifstream fin(filename, ifstream::binary);
    leaf k;
    leaf_bits v;
    for (;!fin.eof();) {
        fin.read((char*)&k, leaf_size);
        fin.read((char*)&v, leaf_bits_size);
        newhm.insert(std::make_pair(k, v));
    }
    fin.close();
    ASSERT_TRUE(true);
    const string outfile = "tw_kL8_lastlevel.bin";
    ofstream fout(outfile, ofstream::binary);
    for ( auto p: newhm ) {
        fout.write((char*) &p.second, leaf_bits_size);
    }
    fout.close();
}
*/
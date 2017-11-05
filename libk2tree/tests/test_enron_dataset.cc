#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <k2tree.h>
#include <gtest/gtest.h>
#include <cassert>
#include <cstdio>
#include <gd.h>
#include "queries.h"

#include <chrono>
#include <thread>

using ::libk2tree::K2TreeBuilder;
using ::libk2tree::HybridK2Tree;
using ::libk2tree::CompressedHybrid;
using ::std::ifstream;
using ::std::ofstream;
using ::std::string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::cout;
using ::std::endl;

int get_edge(const std::string& s, uint& start, uint& end, const std::string& c) {
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
    pos1 = 0;
    if (pos2 == string::npos) return -1;
    start = std::stoi(s.substr(pos1, pos2-pos1)) - 1;
    pos1 = pos2 + c.size();
    if (pos1 == s.size()) return -2;
    end = std::stoi(s.substr(pos1)) - 1;
    if (end == -1) return -2;
    return 0;
}

shared_ptr<CompressedHybrid> Build(vector<vector<bool>> *matrix, 
                                   const string filename, uint n, uint e) {
    K2TreeBuilder tb(n, 4, 2, 8, 4);
    matrix->resize(n, vector<bool>(n, false));
  
    ifstream in(filename, ifstream::in);
    string line;
    uint start, end;
    while(std::getline(in, line)) {
        get_edge(line, start, end, "\t");
        (*matrix)[start][end] = true;
        tb.AddLink(start, end);
    }

    shared_ptr<HybridK2Tree > tree = tb.Build();
    in.close();
    return tree->CompressLeaves();
}


TEST(TwitterDataset, EnronDirectLink) {
    const string filename = "/mnt/disk1/zhaocheng/dataset/enron/enron.nohead.csv";
    const size_t node_num = 69244, edge_num = 276143;

    size_t k1, k2, kL, k1_levels;

    const string config_file = "enron_hybrid.config";
    ifstream config_in(config_file, ifstream::in);
    config_in >> k1 >> k2 >> kL >> k1_levels;
    config_in.close();
    printf("%d %d %d %d\n", k1, k2, kL, k1_levels);

    K2TreeBuilder tb(node_num, k1, k2, kL, k1_levels);
    ifstream in(filename, ifstream::in);
    ASSERT_EQ(in.fail(), false);
    string line;
    uint start=0, end=0;
    while(std::getline(in, line)) {
        int tmp = get_edge(line, start, end, ",");
        ASSERT_NE(tmp, -1);
        if (tmp == -2) 
            continue;
        tb.AddLink(start, end);
    }
    fprintf(stderr, "Internal_nodes: %d\n", tb.internal_nodes());
  
    shared_ptr<HybridK2Tree > tree = tb.Build();
    tb.Clear();

    const string outfile = "/mnt/disk1/zhaocheng/dataset/enron/k2tree/enron.tree";
    ofstream out(outfile, ofstream::out);
    tree->Save(&out);
    out.close();
    cout << "Size of enron bitmap: " << tree->GetSize() << endl;   
    auto ws = tree->WordSize();
    cout << "Word size of enron: " << ws << endl;   
    
    //std::this_thread::sleep_for(std::chrono::seconds(30));
    in.close();
}
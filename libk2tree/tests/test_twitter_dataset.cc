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
#include <gd.h>
#include "queries.h"

#include <chrono>
#include <thread>

using ::libk2tree::K2TreeBuilder;
using ::libk2tree::HybridK2Tree;
using ::libk2tree::CompressedHybrid;
using ::libk2tree::K2TreePartitionBuilder;
using ::libk2tree::utils::Ceil;
using ::libk2tree::K2TreePartition;
using ::libk2tree::CompressedPartition;
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

shared_ptr<K2TreePartition> BuildPartition(vector<vector<int>> matrix, 
    const string &filename, const uint &node_num, const uint &edge_num) {

    uint n = node_num;
    uint k0 = (uint)ceil(sqrt(edge_num));
    uint subm = (uint)ceil((double)n/k0);
  
    K2TreePartitionBuilder b(n, subm, k0, 4, 2, 2, 3, filename);
    for (uint row = 0; row < k0; ++row) {
        for (uint col = 0; col < k0; ++col) {
            for (uint i = 0; i < subm; ++i) {
                for (uint j = 0; j < subm; ++j) {
                    //if ((*matrix)[i + row*subm][j + col*subm])
                    if (std::find(matrix[i+row*subm].begin(), 
                                  matrix[i+row*subm].end(), j+col*subm)
                                  != matrix[i+row*subm].end())
                        b.AddLink(i + row*subm, j + col*subm);
                    }
            }
            b.BuildSubtree();
        }
    }
    ifstream in(filename, ifstream::in);
    shared_ptr<K2TreePartition> t(new K2TreePartition(&in));
    in.close();
    //remove(filename);
    return t;
}

int read_data(const string &filename, const size_t &node_num,
    const size_t &edge_num, vector<vector<int>> &matrix) {
    ifstream in(filename, ifstream::in);
    assert(in.fail() == false);

    matrix.resize(node_num);

    size_t start = 0, end = 0;
    double line_num = 0;
    while (line_num <= edge_num) {

        in >> start >> end;
        start -= 1;
        end -= 1;

        matrix[start].push_back(end);

        if (!((size_t)line_num % 1000000)) {
            fprintf(stderr, "<%d, %d>\n", start, end);
            fprintf(stderr, "%.2f\%\n", line_num/edge_num*100);
        }

        ++line_num;
    }
    printf("Capacity: %d\n", matrix.capacity());
    return 0;
}

TEST(Twitter, build_partition) {
    const string filename = "/mnt/disk1/zhaocheng/dataset/twitter-2010/twitter-2010.csv";
    const size_t node_num = 41652230, edge_num = 1468365182;
   
    vector<vector<int>> matrix;
    read_data(filename, node_num, edge_num, matrix);

    const string outfile = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree/twitter-partition.tree";
    shared_ptr<K2TreePartition> t = BuildPartition(matrix, outfile, node_num, edge_num); 
    cout << "Twitter bitmap size: " << t->GetSize() << endl;
}

/*
int main(int argc, char** argv) {
    const string filename = "/mnt/disk1/zhaocheng/dataset/twitter-2010/twitter-2010.csv";
    const size_t node_num = 41652230, edge_num = 1468365182;

    size_t k1, k2, kL, k1_levels;
    if (argc <= 2) {
        k1 = 8;
        k2 = 4;
        kL = 8;
        k1_levels = 6;
    } else {
        k1 = atoi(argv[1]);
        k2 = atoi(argv[2]);
        kL = atoi(argv[3]);
        k1_levels = atoi(argv[4]);
    }

    vector<vector<int>> matrix;
    read_data(filename, node_num, edge_num, matrix);

    const string outfile = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree/twitter-partition.tree";
    shared_ptr<K2TreePartition> t = BuildPartition(matrix, outfile, node_num, edge_num);

}
*/
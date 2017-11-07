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
using ::boost::filesystem::remove;
using ::std::ifstream;
using ::std::ofstream;
using ::std::string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::cout;
using ::std::endl;

int get_edge(const std::string& s, size_t& start, size_t& end, const std::string& c) {
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

int read_data(const string &filename, const size_t &node_num,
    const size_t &edge_num, vector<vector<int>> &matrix) {
    ifstream in(filename, ifstream::in);
    assert(in.fail() == false);

    matrix.resize(node_num);

    string line;
    size_t start = 0, end = 0;
    double line_num = 0;
    while (std::getline(in, line)) {
        ++line_num;

        int tmp = get_edge(line, start, end, ",");
        assert(tmp != -1);

        if (tmp == -2) 
            continue;

        matrix[start].push_back(end);

    }
    printf("Capacity: %d\n", matrix.capacity());
    return 0;
}

int read_data(const string &filename, const size_t &node_num,
    const size_t &edge_num, bool** &matrix) {
    ifstream in(filename, ifstream::in);
    assert(in.fail() == false);

    matrix = new bool*[node_num];
    for (int i = 0; i < node_num; ++i) {
        matrix[i] = new bool[node_num];
        memset(matrix[i], false, node_num);
    }

    string line;
    size_t start = 0, end = 0;
    double line_num = 0;
    while (std::getline(in, line)) {
        ++line_num;

        int tmp = get_edge(line, start, end, ",");
        assert(tmp != -1);

        if (tmp == -2) 
            continue;

        matrix[start][end] = true;

    }
    return 0;
}

shared_ptr<K2TreePartition> BuildPartition(vector<vector<int>> matrix, 
    const uint &node_num, const uint &edge_num) {

    uint n = node_num;
    //uint k0 = (uint)ceil(sqrt(edge_num));
    uint k0 = 16;
    uint subm = (uint)ceil((double)n/k0);
    printf ("k0: %d, subm: %d\n", k0, subm);
    string filename = "partition_test";
  
    K2TreePartitionBuilder b(n, subm, k0, 4, 2, 2, 3, filename);
    for (uint row = 0; row < k0; ++row) {
        for (uint col = 0; col < k0; ++col) {
            for (uint i = 0; i < subm; ++i) {
                for (uint j = 0; j < subm; ++j) {
                    //if ((*matrix)[i + row*subm][j + col*subm])
                    cnt_size p = i + row*subm, q = j + col*subm;
                    if (std::find(matrix[p].begin(), matrix[p].end(), q) != matrix[p].end()) {
                        b.AddLink(p, q);
                    }
                }
            }
            b.BuildSubtree();
        }
        printf("Finish row%d.\n", row);
    }
    ifstream in(filename, ifstream::in);
    shared_ptr<K2TreePartition> t(new K2TreePartition(&in));
    in.close();
    //remove(filename);
    return t;
}

shared_ptr<K2TreePartition> BuildPartition(bool** matrix, 
    const uint &node_num, const uint &edge_num) {

    uint n = node_num;
    //uint k0 = (uint)ceil(sqrt(edge_num));
    uint k0 = 16;
    uint subm = (uint)ceil((double)n/k0);
    printf ("k0: %d, subm: %d\n", k0, subm);
    string filename = "partition_test";
  
    K2TreePartitionBuilder b(n, subm, k0, 4, 2, 2, 3, filename);
    for (uint row = 0; row < k0; ++row) {
        for (uint col = 0; col < k0; ++col) {
            for (uint i = 0; i < subm; ++i) {
                for (uint j = 0; j < subm; ++j) {
                    //if ((*matrix)[i + row*subm][j + col*subm])
                    cnt_size p = i + row*subm, q = j + col*subm;
                    if (p < node_num && q < node_num && matrix[p][q]) {
                        b.AddLink(p, q);
                    }
                }
            }
            b.BuildSubtree();
        }
        printf("Finish row%d.\n", row);
    }
    ifstream in(filename, ifstream::in);
    shared_ptr<K2TreePartition> t(new K2TreePartition(&in));
    in.close();
    //remove(filename);
    return t;
}


shared_ptr<CompressedPartition> BuildCompressedPartition(bool** matrix, 
    const uint &node_num, const uint &edge_num) {

    uint n = node_num;
    //uint k0 = (uint)ceil(sqrt(edge_num));
    uint k0 = 16;
    uint subm = (uint)ceil((double)n/k0);
    printf ("k0: %d, subm: %d\n", k0, subm);
    string tmp = "partition_test";
  
    K2TreePartitionBuilder b(n, subm, k0, 4, 2, 2, 3, tmp);
    for (uint row = 0; row < k0; ++row) {
        for (uint col = 0; col < k0; ++col) {
            for (uint i = 0; i < subm; ++i) {
                for (uint j = 0; j < subm; ++j) {
                    //if ((*matrix)[i + row*subm][j + col*subm])
                    cnt_size p = i + row*subm, q = j + col*subm;
                    if (p < node_num && q < node_num && matrix[p][q]) {
                        b.AddLink(p, q);
                    }
                }
            }
            b.BuildSubtree();
        }
        printf("Finish row%d.\n", row);
    }
    ifstream in(tmp, ifstream::in);
    shared_ptr<K2TreePartition> t(new K2TreePartition(&in));
    in.close();

    string filename = "compressed_partition";
    ofstream out(filename, ofstream::out);
    t->CompressLeaves(&out);
    out.close();
    
    in.open(filename, ifstream::in);
    shared_ptr<CompressedPartition> tree(new CompressedPartition(&in));
    in.close();

    remove(tmp);
    remove(filename);
    return tree;
}

void delete_matrix(bool** &matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

void delete_matrix(int** &matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

bool** matrix;
const string filename = "/mnt/disk1/zhaocheng/dataset/enron/enron.nohead.csv";
const size_t node_num = 69244, edge_num = 276143;
TEST(Enron, read_data) {
    ASSERT_EQ(read_data(filename, node_num, edge_num, matrix), 0);
}

TEST(Enron, build_partion) {
    const string outfile = "/mnt/disk1/zhaocheng/dataset/enron/k2tree/enron_partition.tree";

    shared_ptr<K2TreePartition> t = BuildPartition(matrix, node_num, edge_num);
    cout << "Enron k2tree size: " << t->GetSize() << "B" << endl;

    ofstream out;
    out.open(outfile, ofstream::out);
    t->Save(&out);
    out.close();

    ASSERT_EQ(1, 1);
}

TEST(Enron, build_compressed_partition) {
    const string outcompressedfile = "/mnt/disk1/zhaocheng/dataset/enron/k2tree/enron_compressed_partition.tree";
    shared_ptr<CompressedPartition> tree = BuildCompressedPartition(matrix, node_num, edge_num);
    cout << "Enron compressed k2tree size: " << tree->GetSize() << "B" << endl;

    ofstream out;
    out.open(outcompressedfile, ofstream::out);
    tree->Save(&out);
    out.close();

    ASSERT_TRUE(true);
    delete_matrix(matrix, node_num);
}
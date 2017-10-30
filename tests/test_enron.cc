#include <k2tree.h>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <cassert>

using k2tree::naive_k2tree;
using std::vector;
using std::unordered_set;
using std::string;
using std::ifstream;

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

        if (!((size_t)line_num % 1000)) {
            fprintf(stderr, "<%d, %d>\n", start, end);
            fprintf(stderr, "%.2f\%\n", line_num/edge_num*100);
        }
        line.clear();
        line.shrink_to_fit();

    }
    printf("Capacity: %d\n", matrix.capacity());
    return 0;
}

TEST(Twitter, build) {
    vector<vector<int>> matrix;
    const string filename = "/mnt/disk1/zhaocheng/dataset/enron/enron.nohead.csv";
    const size_t node_num = 69244, edge_num = 276143;
    ASSERT_EQ(read_data(filename, node_num, edge_num, matrix), 0);

    naive_k2tree nk(4);
    
    nk.build_naive_k2tree(matrix, 131072, 1, 0, 0);
    nk.show_T();
    nk.show_L();
    ASSERT_EQ(1, 1);
}
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

TEST(Twitter, build) {
    vector<vector<int>> matrix;
    const string filename = "/mnt/disk1/zhaocheng/dataset/twitter-2010/twitter-2010.csv";
    const size_t node_num = 41652230, edge_num = 1468365182;
    ASSERT_EQ(read_data(filename, node_num, edge_num, matrix), 0);

    /*
    naive_k2tree nk;
    nk.build_naive_k2tree(matrix, 67108864, 1, 0, 0);
    nk.show_T();
    nk.show_L();
    ASSERT_EQ(1, 1);
    */
}
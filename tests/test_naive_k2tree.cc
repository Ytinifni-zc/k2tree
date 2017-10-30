#include <k2tree.h>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>

using k2tree::naive_k2tree;
using std::pair;

/*
 * 0 1 0 0 | 0 0 0 0 | 0 0 0
 * 0 0 1 1 | 1 0 0 0 | 0 0 0
 * 0 0 0 0 | 0 0 0 0 | 0 0 0
 * 0 0 0 0 | 0 0 0 0 | 0 0 0
 * -------------------------
 * 0 0 0 0 | 0 0 0 0 | 0 0 0
 * 0 0 0 0 | 0 0 0 0 | 0 0 0
 * 0 0 0 0 | 0 0 0 0 | 0 0 0
 * 0 0 0 0 | 0 0 1 0 | 0 0 0
 * -------------------------
 * 0 0 0 0 | 0 0 1 0 | 0 1 0
 * 0 0 0 0 | 0 0 1 0 | 1 0 1
 * 0 0 0 0 | 0 0 1 0 | 0 1 0
 */

void build_matrix(vector<vector<bool> > &matrix, int n=16) {
    matrix.resize(n, vector<bool>(n, false));
    matrix[0][1] = true;
    matrix[1][2] = true;
    matrix[1][3] = true;
    matrix[1][4] = true;
    matrix[7][6] = true;
    matrix[8][6] = true;
    matrix[8][9] = true;
    matrix[9][6] = true;
    matrix[9][8] = true;
    matrix[9][10] = true;
    matrix[10][6] = true;
    matrix[10][9] = true;
}

void print_matrix(vector<vector<bool> > matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j]) printf("%d ", 1);
            else printf("%d ", 0);
        }
        printf("\n");
    }
}

TEST(NaiveK2tree, build) {
    naive_k2tree nk;
    vector<vector<bool> > matrix;
    build_matrix(matrix);
    nk.build_naive_k2tree(matrix);
    nk.show_T();
    nk.show_L();
}

TEST(NaiveK2tree, build_k4) {
    naive_k2tree nk(4);
    vector<vector<bool> > matrix;
    build_matrix(matrix);
    nk.build_naive_k2tree(matrix);
    nk.show_T();
    nk.show_L();
}

TEST(NaiveK2tree, children) {
    naive_k2tree nk;
    vector<vector<bool> > matrix;
    build_matrix(matrix);
    nk.build_naive_k2tree(matrix); 
    pair<size_t, size_t> ch;
    size_t cnt_1s = nk.children(0, ch);
    ASSERT_EQ(cnt_1s, 3);
    ASSERT_EQ(ch.first, 4);
    ASSERT_EQ(ch.second, 7);
    cnt_1s = nk.children(9, ch);
    ASSERT_EQ(cnt_1s, 2);
    ASSERT_EQ(ch.first, 28);
    ASSERT_EQ(ch.second, 31);
    cnt_1s = nk.children(32, ch);
    ASSERT_EQ(cnt_1s, 2);
    ASSERT_EQ(ch.first, 24+36);
    ASSERT_EQ(ch.second, 27+36);
}

/*
int main () {
    naive_k2tree nk;
    vector<vector<bool> > matrix;
    build_matrix(matrix);
    print_matrix(matrix);
    nk.build_naive_k2tree(matrix);
    nk.show_T();
    nk.show_L();
}
*/
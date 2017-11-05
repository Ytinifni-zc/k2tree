/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * ----------------------------------------------------------------------------
 */


#include <k2tree.h>
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "queries.h"
//#include "queries.cc"

using ::libk2tree::K2TreeBuilder;
using ::libk2tree::HybridK2Tree;
using ::libk2tree::CompressedHybrid;
using ::std::shared_ptr;
using ::std::vector;
using ::std::pair;
using ::std::ifstream;
using ::std::ofstream;

shared_ptr<CompressedHybrid> Build(vector<vector<bool>> *matrix, uint e = 0) {
  uint n = rand()%50000+1;
  K2TreeBuilder tb(n, 4, 2, 8, 4);
  matrix->resize(n, vector<bool>(n, false));

  if (e == 0)
    e = n > 100 ? (uint) rand()%(n/100) + 1 : 1;
  for (uint i = 0; i < e; ++i) {
    uint p = (uint) rand()%n;
    uint q = (uint) rand()%n;
    (*matrix)[p][q] = true;
    tb.AddLink(p, q);
  }
  shared_ptr<HybridK2Tree > tree = tb.Build();
  return tree->CompressLeaves();
}

TEST(CompressedHybrid, DirectLinks) {
  time_t t = time(NULL);
  fprintf(stderr, "TIME: %ld\n", t);
  srand((uint) t);
  vector<vector<bool>> matrix;
  shared_ptr<CompressedHybrid> tree = Build(&matrix);

  TestDirectLinks(*tree, matrix);
}

TEST(CompressedHybrid, InverseLinks) {
  vector<vector<bool>> matrix;
  shared_ptr<CompressedHybrid> tree = Build(&matrix);

  TestInverseLinks(*tree, matrix);
}
TEST(CompressedHybrid, CheckLink) {
  vector<vector<bool>> matrix;
  shared_ptr<CompressedHybrid> tree = Build(&matrix);

  TestCheckLink(*tree, matrix);
}
TEST(CompressedHybrid, RangeQuery) {
  vector<vector<bool>> matrix;
  shared_ptr<CompressedHybrid> tree = Build(&matrix);

  TestRangeQuery(*tree, matrix);
}
TEST(CompressedHybrid, Save) {
  vector<vector<bool>> matrix;
  shared_ptr<CompressedHybrid> tree = Build(&matrix);

  ofstream out("compressed_k2tree_test", ofstream::out);
  tree->Save(&out);
  out.close();

  ifstream in("compressed_k2tree_test", ifstream::in);
  CompressedHybrid tree2(&in);
  in.close();

  ASSERT_TRUE(*tree == tree2);


  remove("compressed_k2tree_test");
}

// EMPTY
TEST(CompressedHybrid, Empty) {
  vector<vector<bool>> matrix;
  shared_ptr<CompressedHybrid> tree = Build(&matrix, 0);

  TestCheckLink(*tree, matrix);
  TestDirectLinks(*tree, matrix);
  TestInverseLinks(*tree, matrix);
  TestRangeQuery(*tree, matrix);


  ofstream out("compressed_k2tree_test", ofstream::out);
  tree->Save(&out);
  out.close();

  ifstream in("compressed_k2tree_test", ifstream::in);
  CompressedHybrid tree2(&in);
  in.close();

  TestCheckLink(tree2, matrix);
  TestDirectLinks(tree2, matrix);
  TestInverseLinks(tree2, matrix);
  TestRangeQuery(tree2, matrix);
  remove("compressed_k2tree_test");
}

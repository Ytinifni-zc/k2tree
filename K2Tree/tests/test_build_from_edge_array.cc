#include <gtest/gtest.h>
#include <k2tree.h>
#include "tests_utils.h"

using namespace libk2tree;

TEST(BuildFromEdgeArray, indochina) {
    auto tree = build_k2tree_from_edge_array("indochina");
    const vector<size_t> children8 = {7274693};
    const vector<size_t> children10000 = {5252, 9998, 10008, 10009, 10010, 10021, 10022, 10023, 10025, 10026, 10028, 10029, 10032, 10033, 10034, 10036};
    ASSERT_EQ(tree->get_children(8), children8);
    ASSERT_EQ(tree->get_children(10000), children10000);
}

TEST(BuildFromEdgeArray, twitter2214) {
    auto tree = build_k2tree_from_edge_array("twitter", 2, 2, 1, 4);
    const vector<size_t> children1 = {41652230};
    const vector<size_t> children5000000 = {232013, 1339178, 1339258, 1339875, 4999990, 10338845, 14754360, 21750302, 27466505, 30520559};
    ASSERT_EQ(tree->get_children(1), children1);
    ASSERT_EQ(tree->get_children(5000000), children5000000);
}

TEST(BuildFromEdgeArray, twitter2218) {
    auto tree = build_k2tree_from_edge_array("twitter", 2, 2, 1, 8);
    const vector<size_t> children1 = {41652230};
    const vector<size_t> children5000000 = {232013, 1339178, 1339258, 1339875, 4999990, 10338845, 14754360, 21750302, 27466505, 30520559};
    ASSERT_EQ(tree->get_children(1), children1);
    ASSERT_EQ(tree->get_children(5000000), children5000000);
}

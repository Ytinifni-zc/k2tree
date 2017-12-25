#include <gtest/gtest.h>
#include "tests_utils.h"

using namespace libk2tree;
using namespace std;

TEST(BFS, test_tree) {
    auto kt = read_test_graph();
    kt->BFS();
}

TEST(BFS, twiiter) {
    shared_ptr<k2tree> kt;
    utils::cost([&](){
        kt = read_twitter();
    });

    utils::cost([=](){
        kt->BFS();
    });
}

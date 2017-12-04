//
// Created by inFinity on 2017/11/30.
//

#include <gtest/gtest.h>
#include "tests_utils.h"

using namespace libk2tree;
using namespace std;

void show_children(const vector<size_t> &children) {
    for (auto child : children) {
        cout << child << " ";
    }
    cout << endl;
}

TEST(GetChild, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(9));
    show_children(kt.get_parents(9));

}

TEST(GetChild, test_csv_kl4) {

    const string path = "./k2tree/kl4/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 4, node_num, path, libk2tree::read_T);

    show_children(kt.get_children(10));
    show_children(kt.get_parents(10));
    show_children(kt.get_parents(2));
    show_children(kt.get_parents(7));
}

TEST(GetChild, twitter0_kl4) {
    auto kL = 4;
    auto kt = read_twitter_partition(0, kL);

    show_children(kt->get_children(27));
    show_children(kt->get_parents(27));

    auto ktc = read_twitter_partition_compressed(0, kL);
    show_children(ktc->get_children(27));
    show_children(ktc->get_parents(27));

}

TEST(GetChild, twitter0_kl8) {
    auto kL = 8;
    auto kt = read_twitter_partition(0, kL);

    show_children(kt->get_children(27));
    show_children(kt->get_parents(27));

    auto ktc = read_twitter_partition_compressed(0, kL);
    show_children(ktc->get_children(27));
    show_children(ktc->get_parents(27));
}

TEST(GetChild, twitter0_kl16) {
    auto kL = 16;
    auto kt = read_twitter_partition(0, kL);

    show_children(kt->get_children(27));
    show_children(kt->get_parents(27));

    auto ktc = read_twitter_partition_compressed(0, kL);
    show_children(ktc->get_children(27));
    show_children(ktc->get_parents(27));
}

TEST(GetChild, twitter8514_kl16) {
    auto kL = 16;
    auto kt = read_twitter_partition(8514, kL);

    show_children(kt->get_children(325409));
    show_children(kt->get_parents(325409));

    auto ktc = read_twitter_partition_compressed(8514, kL);
    show_children(ktc->get_children(325409));
    show_children(ktc->get_parents(325409));
}

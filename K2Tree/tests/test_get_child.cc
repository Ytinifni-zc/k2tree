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

TEST(GetChild, twitter) {
    shared_ptr<k2tree> kt;
    utils::cost([&](){
        kt = read_twitter();
    });

    utils::cost([=]() {
        auto most_degree = 5000000;
        std::cerr << most_degree << "=> { ";
        std::cerr << kt->get_children(most_degree) << " } \t";
    }, "us");

    utils::cost([=]() {
        auto most_degree = 100000;
        std::cerr << most_degree << "=> { ";
        std::cerr << kt->get_children(most_degree) << " } \t";
    }, "us");

    utils::cost([=]() {
        auto most_degree = 23934134;
        std::cerr << most_degree << "=> {...}.size(): ";
        std::cerr << kt->get_children(most_degree).size() << "\t";
    }, "us");

    auto rand_size = 100000;
    auto r100 = 100;
    vector<int> rand_100, rand_10000;
    utils::cost([&]() {
        std::cerr << "Generate rand node vector(100 and 10000). \t";
        rand_100.resize(r100);
        rand_10000.resize(rand_size);
        for (int i = 0; i < rand_size; ++i) {
          if(i < r100) rand_100[i] = std::rand() % TWITTER_NODE_NUM;
          rand_10000[i] = std::rand() % TWITTER_NODE_NUM;
        }
    });

    auto size_100 = 0, size_10000 = 0;
    utils::cost([&]() {
        std::cerr << "Find 100 node's children. \t";
        for (auto _n : rand_100)
          kt->get_children(_n);
          //size_100 += kt->get_children(_n).size();
    });
    //bit_vector ttt;
    //utils::cost([&](){
    //        std::cerr << "ttt = kt.T_ \t";
    //        ttt = kt->T();
    //        });
    /*
    utils::cost([&]() {
        //int cnt = 0;
        std::cerr << "Find " << rand_size << " node's children. \t";
        for (auto _n : rand_10000)
          kt->get_children(_n);
          //(ttt[_n]==1);
          //size_10000 += kt->get_children(_n).size();
    });
    */
}

TEST(GetChild, indochina) {
    shared_ptr<k2tree> kt;
    utils::cost([&](){
        kt = read_indochina();
    });
    utils::cost([&](){
        auto _n = 10000;
        std::cerr << "Get " << _n << "'s child: {"
                  << kt->get_children(_n) << "} \t";
    }, "us");
    utils::cost([&](){
        auto _n = 8;
        std::cerr << "Get " << _n << "'s child: {"
                << kt->get_children(_n) << "} \t";
    }, "us");

    utils::cost([&](){
        auto _n = 1525;
        std::cerr << "Get " << _n << "'s child: {"
                  << kt->get_children(_n) << "} \t";
    }, "us");

    auto rand_size = 100000;
    auto r100 = 100;
    vector<int> rand_100, rand_10000;
    utils::cost([&]() {
        std::cerr << "Generate rand node vector(100 and 10000). \t";
        rand_100.resize(r100);
        rand_10000.resize(rand_size);
        for (int i = 0; i < rand_size; ++i) {
          if(i < r100) rand_100[i] = std::rand() % INDOCHINA_NODE_NUM;
          rand_10000[i] = std::rand() % INDOCHINA_NODE_NUM;
        }
    });

    auto size_100 = 0, size_10000 = 0;
    utils::cost([&]() {
        std::cerr << "Find 100 node's children. \t";
        for (auto _n : rand_100)
          kt->get_children(_n);
          //size_100 += kt->get_children(_n).size();
    });
    utils::cost([&]() {
        std::cerr << "Find " << rand_size << " node's children. \t";
        for (auto _n : rand_10000)
          kt->get_children(_n);
          //size_10000 += kt->get_children(_n).size();
    });
}

TEST(GetChild, twitter0_kl4) {
    auto kL = 4;
    auto kt = read_twitter_p0();

    utils::cost([=](){
        cerr << "27-> " << kt->get_children(27) << endl;
    }, "us");
    utils::cost([=](){
        cerr << "500-> " << kt->get_children(500) << endl;
    }, "us");
    cerr << "->27: " << kt->get_parents(27) << endl;

}

/*
TEST(GetChild, test_csv) {

    const string path = "./k2tree/";
    const size_t node_num = 11;
    libk2tree::k2tree kt(2, 2, 1, 2, node_num, path, libk2tree::read_T);

    utils::cost([&](){
    show_children(kt.get_children(9));
      }, "us");
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
*/

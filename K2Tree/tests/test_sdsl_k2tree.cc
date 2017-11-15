//
// Created by inFinity on 2017/11/14.
//

#include <gtest/gtest.h>
#include <sdsl/k2_tree.hpp>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <sdsl/io.hpp>
#include <iostream>

using namespace std;
//using namespace sdsl;

TEST(sdsl_k2tree, read_from_testcsv) {
    string file = "../test.csv";
    size_t node_num = 11, edge_num = 12;
    vector<tuple<uint64_t, uint64_t>> edges(edge_num);

    ifstream in(file, ifstream::in);

    double line_num = 0;
    uint64_t u, v;
    while (line_num < edge_num) {

        in >> u >> v;
        u --; v--;

        edges[line_num] = tuple<uint64_t, uint64_t>(u, v);
        if (!((size_t)line_num % 1000000)) {
            fprintf(stderr, "<%d, %d>\n", u, v);
            fprintf(stderr, "%.2f%\n", line_num/edge_num*100);
        }
        line_num++;

    }

    in.close();

    sdsl::k2_tree<2> k2tree(edges, node_num);
    auto t = k2tree.get_t();
    cout << t.size() << endl;
    for (auto b: t)
        cout << b;
    cout << endl;
    auto l = k2tree.get_l();
    cout << l.size() << endl;
    for (auto b: l)
        cout << b;
    cout << endl;
    sdsl::store_to_file(k2tree, "test.tree");
}

TEST(sdsl_k2tree, read_from_twitter) {
    string file = "/mnt/disk1/zhaocheng/dataset/twitter-2010/twitter-2010.csv";
    size_t node_num = 41652230, edge_num = 1468365182;
    vector<tuple<uint64_t, uint64_t>> edges(edge_num);

    ifstream in(file, ifstream::in);

    double line_num = 0;
    uint64_t u, v;
    while (line_num < edge_num) {

        in >> u >> v;
        u --; v--;

        edges[line_num] = tuple<uint64_t, uint64_t>(u, v);
        if (!((size_t)line_num % 1000000)) {
            fprintf(stderr, "<%d, %d>\n", u, v);
            fprintf(stderr, "%.2f%\n", line_num/edge_num*100);
        }
        line_num++;

    }

    in.close();

    sdsl::k2_tree<2> k2tree(edges, node_num);
    cout << "constructed." << endl;
    /*
    auto t = k2tree.get_t();
    cout << t.size() << endl;
    for (auto b: t)
        cout << b;
    cout << endl;
    auto l = k2tree.get_l();
    cout << l.size() << endl;
    for (auto b: l)
        cout << b;
    cout << endl;
     */
    sdsl::store_to_file(k2tree, "test.tree");
}
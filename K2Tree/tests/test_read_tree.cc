//
// Created by inFinity on 2017/11/7.
//

#include <gtest/gtest.h>
#include <k2tree.h>

using namespace libk2tree;
using namespace std;

//int main() {
TEST(Read, read2k2tree) {

    const string path = "./k2tree/";
//    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree/";
    const string filename = path + "../test.csv";
//    const string filename = path + "../twitter-2010.csv";
    const size_t node_num = 11, edge_num = 11;
//    const size_t node_num = 41652230, edge_num = 1468365182;
    libk2tree::k2tree kt(2, 2, 1, 8, node_num, edge_num, path);
    ASSERT_NE(kt.T().size(), 0);
    ASSERT_NE(kt.L().size(), 0);
    cout << kt.T().size() << endl;
    for (int i = 0; i < kt.T().size(); ++i) {
        cout << kt.T()[i];
    }
    cout << endl;
    cout << kt.L().size() << endl;
    for (int i = 0; i < kt.L().size(); ++i) {
        cout << kt.L()[i];
    }
    cout << endl;

}

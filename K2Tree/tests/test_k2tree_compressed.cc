//
// Created by zhaocheng on 17-11-24.
//

#include <gtest/gtest.h>
#include <k2tree.h>
#include <k2tree_compressed.h>

using std::cout;
using std::endl;
using namespace libk2tree;

void build_and_save_ck2tree(const int &k1, const int &k2, const int &k1_level, const int &kL,
                                            const string &path, const size_t &node_num,
                                            char* ft_file, size_t &edge_num) {
    k2tree_compressed kt(k1, k2, k1_level, kL, node_num, path, libk2tree::read_T);
    kt.build_compressed_leaves();
    saveFT(kt.compressL(), ft_file);
    edge_num = kt.edge_num();
}

TEST(ReadTwitter0, readT_kL4) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl4/";
    const size_t node_num = 325409, edge_num = 578757;
    size_t ret_edge_num = 0;

    char* ft_path = strdup((path + "L_FTR.bin").c_str());

    build_and_save_ck2tree(2, 2, 1, 4, path, node_num, ft_path, ret_edge_num);

    free(ft_path);

    ASSERT_EQ(edge_num, ret_edge_num);

}

TEST(ReadTwitter0, readT_kL8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl8/";
    const size_t node_num = 325409, edge_num = 578757;
    size_t ret_edge_num = 0;

    char * ft_path = strdup((path + "L_FTR.bin").c_str());

    build_and_save_ck2tree(2, 2, 1, 8, path, node_num, ft_path, ret_edge_num);
    free(ft_path);

    ASSERT_EQ(ret_edge_num, edge_num);

}

TEST(ReadTwitter0, readT_kL16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter0.tree/kl16/";
    const size_t node_num = 325409, edge_num = 578757;
    size_t ret_edge_num = 0;

    char * ft_path = strdup((path + "L_FTR.bin").c_str());

    build_and_save_ck2tree(2, 2, 1, 16, path, node_num, ft_path, ret_edge_num);
    free(ft_path);

    ASSERT_EQ(ret_edge_num, edge_num);

}

TEST(ReadTwitter8514, readT_kL4) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl4/";
    const size_t node_num = 325409, edge_num = 215287671;
    size_t ret_edge_num = 0;

    char* ft_path = strdup((path + "L_FTR.bin").c_str());

    build_and_save_ck2tree(2, 2, 1, 4, path, node_num, ft_path, ret_edge_num);

    free(ft_path);

    ASSERT_EQ(edge_num, ret_edge_num);

}

TEST(ReadTwitter8514, readT_kL8) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl8/";
    const size_t node_num = 325409, edge_num = 215287671;
    size_t ret_edge_num = 0;

    char* ft_path = strdup((path + "L_FTR.bin").c_str());

    build_and_save_ck2tree(2, 2, 1, 8, path, node_num, ft_path, ret_edge_num);

    free(ft_path);

    ASSERT_EQ(edge_num, ret_edge_num);

}

TEST(ReadTwitter8514, readT_kL16) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter8514.tree/kl16/";
    const size_t node_num = 325409, edge_num = 215287671;
    size_t ret_edge_num = 0;

    char* ft_path = strdup((path + "L_FTR.bin").c_str());

    build_and_save_ck2tree(2, 2, 1, 16, path, node_num, ft_path, ret_edge_num);

    free(ft_path);

    ASSERT_EQ(edge_num, ret_edge_num);

}



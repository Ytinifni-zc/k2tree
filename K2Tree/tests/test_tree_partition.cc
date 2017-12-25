//
// Created by inFinity on 2017/11/17.
//

#include <gtest/gtest.h>
#include <k2tree_partition.h>
#include <utils/time.h>
#include <utils/time.cc>
#include <fstream>
#include "../tools/config.h"

using namespace libk2tree;

/*
TEST(partition_k2tree, build) {
    int k0 = 128;
    libk2tree::k2tree_partition tree(k0, 2, 2, 1, 4, TWITTER_NODE_NUM, TWITTER_EDGE_NUM);

    string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/";
    vector<string> file_list(k0*k0);
    for (int i = 0; i < k0*k0; ++i) {
        file_list[i] = path + "twitter" + std::to_string(i) + ".csv";
    }
    string store_path = path + "k2tree/";

    tree.build_partition_k2tree(file_list, store_path);
}
*/

TEST(partition_k2tree, build) {
    int k0 = 128;
    int (*data)[2];
    vector<int(*)[2]> edge_lists(k0*k0);
    vector<uint64_t> size_list(k0*k0);
    vector<libk2tree::config> configures(k0*k0);

    for (int i = 0; i < k0*k0; ++i)
        utils::cost([&](){
            std::cerr << "Load edge lists from bin " << i << ": ";
            std::string filename = TWITTER_PATH + "../partition/twitter"
                    + std::to_string(i) + ".bin";
            std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
            long fileSize = in.tellg();
            int fd = open(filename.c_str(), O_RDONLY, 0);
            if (fd == -1) {
                perror("open failed.");
                exit(1);
            }
            void* ptr = mmap(0, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
            if (ptr == MAP_FAILED) {
                perror("mmap failed.");
                exit(1);
            }
            edge_lists[i] = static_cast<int(*)[2]>(ptr);

            size_list[i] = fileSize / 8;
            close(fd);
            in.close();

            configures[i] = std::make_tuple(8, 8, 1, 8, 325409, size_list[i]);
        });

    libk2tree::k2tree_edge_partition kep(k0, configures);
    utils::cost([&](){
        kep.build_from_edge_arrays(edge_lists, size_list);
    });
}

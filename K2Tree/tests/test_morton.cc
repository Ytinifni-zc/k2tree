#include <gtest/gtest.h>
#include <k2tree_morton.h>
#include "tests_utils.h"

using namespace libk2tree;
using namespace std;

TEST(MortonNumber, pair) {
    k2tree_morton<4,2,3,8> tree(TWITTER_NODE_NUM);
    auto morton = tree.kv_2_Zorder(make_pair(0x003311ff, 0x01bbaa88));
    cerr << hex << morton << endl;
    ASSERT_EQ(morton, 0x00012f4f4646eaf8ull);
}

TEST(MortonNumber, indochina) {
    k2tree_morton<4,2,3,8> tree(INDOCHINA_NODE_NUM);
    string filename = INDOCHINA_PATH + "../indochina-2004.bin";
    vector<uint64_t> morton_numbers;
    int (*data)[2];
    long cnt;
    utils::cost([&](){
        std::cerr << "Load edge array from bin: ";
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
        data = static_cast<int(*)[2]>(ptr);

        cnt = fileSize / 8;
        close(fd);
        in.close();
    });
    tree.build_from_edge_array(data, cnt);
}

/*
TEST(MortonNumber, uk_2007_05) {
    k2tree_morton<4,2,3,8> tree(UK2007_NODE_NUM);
    string filename = UK2007_PATH + "uk-2007-05.bin";
    vector<uint64_t> morton_numbers;
    int (*data)[2];
    long cnt;
    utils::cost([&](){
        std::cerr << "Load edge array from bin: ";
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
        data = static_cast<int(*)[2]>(ptr);

        cnt = fileSize / 8;
        close(fd);
        in.close();
    });
    tree.build_from_edge_array(data, cnt);
}
*/

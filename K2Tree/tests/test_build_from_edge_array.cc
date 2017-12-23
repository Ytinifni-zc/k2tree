#include <gtest/gtest.h>
#include <k2tree.h>
#include <fstream>
#include <utils/time.h>
#include <utils/time.cc>
#include "../tools/config.h"

using namespace libk2tree;

TEST(BuildFromEdgeArray, test1) {
  int (*data)[2];
  long cnt;
  //int k1 = 8, k2 = 8, k1_levels = 1, kL = 8, node_num = 325409, edge_num = 578756;
  //int k1 = 8, k2 = 8, k1_levels = 1, kL = 8, node_num = INDOCHINA_NODE_NUM, edge_num = INDOCHINA_EDGE_NUM;
  int k1 = 4, k2 = 4, k1_levels = 1, kL = 4, node_num = INDOCHINA_NODE_NUM, edge_num = INDOCHINA_EDGE_NUM;
  utils::cost([&](){
      std::cerr << "Load edge array from bin: ";
      std::string filename = INDOCHINA_PATH + "../indochina-2004.bin";
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
      in.close();
  });
  k2tree tree(k1, k2, k1_levels, kL, node_num, edge_num);
  tree.build_from_edge_array_csv(data, cnt);
  const vector<size_t> children8 = {7274693};
  const vector<size_t> children10000 = {5252, 9998, 10008, 10009, 10010, 10021, 10022, 10023, 10025, 10026, 10028, 10029, 10032, 10033, 10034, 10036};
  ASSERT_EQ(tree.get_children(8), children8);
  ASSERT_EQ(tree.get_children(10000), children10000);
  utils::cost([&](){
      std::cerr << "Store to file." << std::endl;
      sdsl::store_to_file(tree.T(), INDOCHINA_PATH+"T.bin");
      sdsl::store_to_file(tree.L(), INDOCHINA_PATH+"L.bin");
  });
}

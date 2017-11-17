//
// Created by inFinity on 2017/11/16.
//

#include <k2tree.h>
#include <k2tree_partition.h>
#include <thread>

k2tree::k2tree_partition::k2tree_partition(int k0_, int k1_, int k2_, int k1_levels_, int kL_,
                                           size_t node_num_, size_t edge_num_) :
        k0_(k0_), k2tree(k1_, k2_, k1_levels_, kL_, node_num_, edge_num_) {}

void k2tree::k2tree_partition::build_partition_k2tree(vector<string> file_list, string store_path) {
    int files_size = file_list.size();
    assert(files_size == k0_*k0_);

    auto build_k2tree = [=](vector<int> file_indice) {
        for (auto i : file_indice) {
            string file = file_list[i];
            build_from_edge_array_csv(file, "", k2tree::to_memory);
        }
    };
}
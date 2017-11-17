//
// Created by inFinity on 2017/11/16.
//

#ifndef K2TREE_K2TREE_PARTITION_H
#define K2TREE_K2TREE_PARTITION_H

#include <k2tree.h>

namespace k2tree {
    class k2tree_partition: public k2tree {
    public:
        explicit k2tree_partition(int k0_, int k1_, int k2_, int k1_levels_, int kL_,
                                  size_t node_num_, size_t edge_num_);

    public:
        void build_partition_k2tree(vector<string> file_list, string store_path);

    private:
        int k0_;

    };
}

#endif //K2TREE_K2TREE_PARTITION_H

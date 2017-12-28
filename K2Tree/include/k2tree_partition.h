//
// Created by inFinity on 2017/11/16.
//

#ifndef K2TREE_K2TREE_PARTITION_H
#define K2TREE_K2TREE_PARTITION_H

#include <k2tree.h>
#include <tuple>

namespace libk2tree {
    class k2tree_partition: public k2tree {
    public:
        explicit k2tree_partition(int k0_, int k1_, int k2_, int k1_levels_, int kL_,
                                  size_t node_num_, size_t edge_num_);

    public:
        void build_partition_k2tree(vector<string> file_list, string store_path);

    private:
        /**
         * Merge partition bitmap from each thread.
         */
        void merge_part_tree_bitmap();

    private:
        int k0_;

        int part_node_num_;
        int part_edge_num_;

        vector<vector<bit_vector> > part_tree_bitmap_;

    };

    using config=std::tuple<int, int, int, int, size_t, size_t>;

    class k2tree_edge_partition {
    public:
        /**
         * @param k0 Split matrix by k0*k0.
         * @param configures Configures of each submatrix which splited by k0*k0.
         */
        k2tree_edge_partition(int k0, vector<config> configures);

        k2tree_edge_partition(int k0, vector<config> configures, vector<std::shared_ptr<k2tree>> kp);

        /**
         * Build partition k2tree from vector of each submatrix' edge list.
         * @param edge_lists Vector of each submatrix' edge list.
         * @param size_list Vector of each edge list.
         */
        void build_from_edge_arrays(vector<int (*)[2]> edge_lists, vector<uint64_t> size_list);

        /**
         * Returen children array of node p.
         * @param p Start from 1.
         * @return Array of children.
         */
        vector<size_t> get_children(size_t p);

        /**
         * Save sub-k2trees.
         */
        void save(std::string path);

        /**
         * Load from sub-k2trees.
         */
        k2tree_edge_partition(const std::string &path);

    private:
        int k0_;
        vector<config> configures_;
        vector<std::shared_ptr<k2tree> > k2tree_parts;
    };
}

#endif //K2TREE_K2TREE_PARTITION_H

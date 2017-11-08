//
// Created by inFinity on 2017/11/7.
//

#ifndef K2TREE_K2TREE_H
#define K2TREE_K2TREE_H

#include <base.h>
#include <build_tree.h>

using namespace k2tree;

namespace k2tree {
    class k2tree {
    public:
        k2tree(const vector<size_t> &ks_, const vector<submat> &T_, const vector<leaf_bits> &L_);
        k2tree(const string &path);

        vector<submat> T();
        vector<leaf_bits> L();
    private:
        vector<size_t> ks_;
        vector<submat> T_;
        vector<leaf_bits> L_;

        size_t rank(size_t pos);
    };
}

#endif //K2TREE_K2TREE_H

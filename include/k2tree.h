#ifndef INCLUDE_K2TREE_H_
#define INCLUDE_K2TREE_H_

#include <base.h>
#include <bit_array.h>
#include <vector>
#include <unordered_set>
//#include <memory>

using ::std::vector;
using ::std::pair;
using ::std::unordered_set;

namespace k2tree {

    class naive_k2tree {
    public:
        naive_k2tree();

        naive_k2tree(size_t k);

        uchar build_naive_k2tree(vector<vector<bool> > matrix, int n, int l, int p, int q);
        uchar build_naive_k2tree(vector<vector<bool> > matrix);

        uchar build_naive_k2tree(vector<vector<int> > matrix, int n, int l, int p, int q);
        uchar build_naive_k2tree(vector<vector<int> > matrix);
        
        // Test
        void show_T();
        void show_L();

    private:
        size_t k_;
        bit_array T_;
        bit_array L_;

        // 存放建树时每层的Tl
        vector<bit_array> Tl_;

        /**
         * node's rank in T_
         * 
         * @param node  Index of node in T_.
         * @return  node's rank in T_.
         */
        size_t rank(size_t node);

    public:
        /** 
         * node's children in k2tree
         * 
         * @param node  Index of node in T_.
         * @return children  node's children array in T_||L_, 
         *                   it records the start and end of indices.
         * @return  Number of 1s in node's children.
         */
        size_t children(size_t node, pair<size_t, size_t> &children);

    };

    
}

#endif
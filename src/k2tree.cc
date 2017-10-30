#include <k2tree.h>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace k2tree;

naive_k2tree::naive_k2tree() : k_(2) {
    T_ = bit_array();
    L_ = bit_array();
}

naive_k2tree::naive_k2tree(size_t k) : k_(k) {
    T_ = bit_array();
    L_ = bit_array();
}

uchar naive_k2tree::build_naive_k2tree(vector<vector<bool> > matrix) {
    // TODO
    return build_naive_k2tree(matrix, matrix.size(), 1, 0, 0);
}

uchar naive_k2tree::build_naive_k2tree(vector<vector<bool> > matrix, int n, int l, int p, int q) {
    // TODO
    bit_array C;
    const int level = ceil(log(matrix.size())/log(k_));
    if (Tl_.empty()) {
        Tl_.resize(level, bit_array());
    }
    bool flag_l = false, flag_t = false;
    for (int i = 0; i < k_; ++i) {
        for (int j = 0; j < k_; ++j) {
            //printf("<n, l, p, q>: <%d, %d, %d, %d>\n", n, l, p, q);
            if (l == level) {
                //L_.add_bit(matrix[p+i][q+j]?1:0);
                C.add_bit(matrix[p+i][q+j]?1:0);
                flag_l = true;
            } else {
                C.add_bit(build_naive_k2tree(matrix, n/k_,l+1,p+i*(n/k_),q+j*(n/k_)));
                flag_t = true;
            }
        }
    }

    if (C.is_equal_0()) return 0;
    if (flag_l) L_.add_bits(C);
    if (flag_t) {
        Tl_[l].add_bits(C);
        if (l == 1) {
            for (auto t: Tl_)
                T_.add_bits(t);
            Tl_.clear();
            Tl_.shrink_to_fit();
        }
    }
    return 1;
}

uchar naive_k2tree::build_naive_k2tree(vector<vector<int> > matrix) {
    // TODO
    return build_naive_k2tree(matrix, matrix.size(), 1, 0, 0);
}

uchar naive_k2tree::build_naive_k2tree(vector<vector<int> > matrix, int n, int l, int p, int q) {
    // TODO
    bit_array C;
    const int level = ceil(log(matrix.size())/log(k_));
    if (Tl_.empty()) {
        Tl_.resize(level, bit_array());
    }
    bool flag_l = false, flag_t = false;
    for (int i = 0; i < k_; ++i) {
        for (int j = 0; j < k_; ++j) {
            //printf("<n, l, p, q>: <%d, %d, %d, %d>\n", n, l, p, q);
            if (l == level) {
                //L_.add_bit(matrix[p+i][q+j]?1:0);
                if (std::find(matrix[p+i].begin(), matrix[p+i].end(), q+j) != matrix[p+i].end())
                    C.add_bit(1);
                else C.add_bit(0);
                flag_l = true;
            } else {
                C.add_bit(build_naive_k2tree(matrix, n/k_,l+1,p+i*(n/k_),q+j*(n/k_)));
                flag_t = true;
            }
        }
    }

    if (C.is_equal_0()) return 0;
    if (flag_l) L_.add_bits(C);
    if (flag_t) {
        Tl_[l].add_bits(C);
        if (l == 1) {
            for (auto t: Tl_)
                T_.add_bits(t);
            Tl_.clear();
            Tl_.shrink_to_fit();
        }
    }
    return 1;
}

void naive_k2tree::show_T() {
    T_.show_bit();
}

void naive_k2tree::show_L() {
    L_.show_bit();
}

size_t naive_k2tree::rank(size_t node) {
    // TODO
    return T_.rank(node);
}

size_t naive_k2tree::children(size_t node, pair<size_t, size_t> &children) {

    children.first = rank(node)*k_*k_;
    children.second = children.first+k_*k_-1;

    size_t cnt_1s = 0;

    if (children.first < T_.length()) {
        for (int i = children.first; i <= children.second ; ++i) {
            if (T_.get_bit(i)) cnt_1s++;
        }
    }
    else {
        for (int i = children.first; i <= children.second ; ++i) {
            if (L_.get_bit(i-T_.length())) cnt_1s++;
        }
    }
    return cnt_1s;
}
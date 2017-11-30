//
// Created by inFinity on 2017/11/7.
//

#ifndef K2TREE_K2TREE_H
#define K2TREE_K2TREE_H

#include <base.h>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <stdint.h>
#include <utils/bit_vector.h>
#include <sdsl/bit_vectors.hpp>
#include <memory>

using namespace libk2tree;
using namespace sdsl;
using std::bitset;
using std::unordered_map;
using std::unordered_set;
using std::shared_ptr;

namespace libk2tree {
    const int to_binary = 0xba;
    const int to_memory = 0xe0;
    const int to_compact_binary = 0xcaca;

    const int read_T_levels = 0x1ead;
    const int read_T = 0x2ead;

    class k2tree {
    public:
        /**
         * Constructor of the basic infomation of k2tree.
         * @param k1_
         * @param k2_
         * @param k1_levels_
         * @param kL_
         * @param node_num_
         * @param edge_num_
         */
        explicit k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_);

        /**
         * Constructor of the whole k2tree.
         * @param k1_
         * @param k2_
         * @param k1_levels_
         * @param kL_
         * @param node_num_
         * @param edge_num_
         * @param T_
         */
        explicit k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_, const bit_vector &T_);

        /**
         * Constructor of the whole k2tree.
         * @param k1_
         * @param k2_
         * @param k1_levels_
         * @param kL_
         * @param node_num_
         * @param edge_num_
         * @param T_
         * @param L_
         */
        explicit k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_, const bit_vector &T_,
               const bit_vector &L_);

        /**
         * Constructor of the basic infomation and k2tree binary files.
         * @param k1_
         * @param k2_
         * @param k1_levels_
         * @param kL_
         * @param node_num_
         * @param path Path of storing k2tree binary files.
         * @param read_flag Constructing k2tree from Tl's bitmap vector or ONE T's bitmap.
         */
        explicit k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, const string &path, const int &read_flag=read_T_levels);

        /**
         * Move constructor
         * @param lhs
         */
        k2tree(k2tree &&lhs);


    public:
        //void T(bit_vector t);
        //void L(bit_vector l);
        bit_vector T();
        bit_vector L();
        vector<bit_vector> tree_bitmap();

        size_t edge_num();

        size_t words_cnt() const {
            return L_.size()/(kL_*kL_);
        }

        size_t words_size() const {
            return static_cast<size_t>(ceil(static_cast<double>(kL_ * kL_) / 8));
        }

        /**
         * Iterates over the words in the leaf level.
         *
         * @param fun Pointer to function, functor or lambda expecting a pointer to
         * each word.
         */
        template <typename Function>
        void words(Function fun) const {
            size_t cnt = words_cnt();
            uint size = words_size();

            size_t bit = 0;
            for (size_t i = 0; i < cnt; ++i) {
                uchar *word = new uchar[size];
                std::fill(word, word+size, 0);
                for (uint j = 0; j < kL_*kL_; ++j, ++bit) {
                    if (L_[bit])
                        word[j/8] |= (uchar) (1<<(j%8));
                }
                fun(word);
                delete[] word;
            }
        }

    private:
        static const size_t __n = 19;
        static const size_t __p = 35;
        typedef bitset<__n> node_bits;
        typedef bitset<__p> submat_pos;
        int leaf_bits;
        int submat1;
        int submat2;


    private:
        void set_tree_unit();

        inline int which_k(int level) {
            return (level == height_) ? kL_ : (
                    (level <= k1_levels_) ? k1_ : k2_
            );
        }

        inline int which_submat(int level) {
            return (level == height_) ? leaf_bits : (
                    (level <= k1_levels_) ? submat1 : submat2
            );
        }

        inline int get_submat_size(const int &size) {
            return (int)ceil(((double)size)/8);
        }

        /**
         * Indicating row and column of this submatrix in current level.
         */
        struct submat_info {
            node_bits u;
            node_bits v;
            submat_info(int _u, int _v) :u(_u), v(_v) {}
            bool operator==(const submat_info &si) const {
                return u == si.u && v == si.v;
            }
        };
        struct submat_info_hash {
            size_t operator()(const submat_info& si) const {
                std::hash<node_bits > hash_fn;
                return hash_fn(si.u << 11) ^ hash_fn(si.v);
            }
        };

        // <pos, submat>
        typedef unordered_map<submat_pos, bit_vector> pos_submat;
        // 上一层中不为0的子阵对应的u,v
        // typedef unordered_set<submat_info, submat_info_hash> level_1s;
        typedef vector<submat_info> level_1s;

        static bool cmp_submat_pos(const submat_pos &p1, const submat_pos &p2) {
            for (int i = __p-1; i >= 0; --i) {
                if (p1[i] == p2[i]) continue;
                if (!p1[i]) return true;
                return false;
            }
        }

        struct cmp_by_submat_pos {
            bool operator() (const submat_pos &k1, const submat_pos &k2) const {
                return cmp_submat_pos(k1, k2);
            }
        };


        /**
         * Calculate position of row @param u colum @param v in level @param level
         * @return position in submatrix (bit_vector<submat_pos>)
         */
        submat_pos get_pos(const int &u, const int &v, const int &level) {

            if (level < 1) return submat_pos(0);

            int k = which_k(level);
            if (level == 1) {
                return submat_pos(u%k*k+v%k);
            }

            unsigned long long pre_pos = get_pos(u/k, v/k, level - 1).to_ulong();
            return submat_pos(pre_pos*k*k+((u%k)*k+v%k));

        }

        void split_T();

        /**
         * Return true iff node p points to q and false otherwise.
         * @param n Current submatrix size.
         * @param p Row in current submatrix.
         * @param q Column in current submatrix.
         * @param pos Position in T||L;
         * @param level Current level of submatrix.
         * @return
         */
        bool check_link_(size_t n, size_t p, size_t q, llong pos, int level);

        /**
         * Return children's id in current level.
         * @param n
         * @param p
         * @param q
         * @param pos
         * @param level
         * @param children Result of children.
         */
        void get_child_(size_t n, size_t p, size_t q, llong pos, int level, vector<size_t> &children);

        /**
         * Return parents' id in current level.
         * @param n
         * @param p
         * @param q
         * @param pos
         * @param level
         * @param parents
         */
        void get_parent_(size_t n, size_t p, size_t q, llong pos, int level, vector<size_t> &parents);

    protected:

        /**
         * Add one submatrix bit to hashmap and last_level hashset.
         * @param hm
         * @param level
         * @param u
         * @param v
         * @param last_level
         */
        void hm_insert_bit(pos_submat &hm, const int &level, const int &u, const int &v, level_1s &last_level);
        void hm_insert_bit(pos_submat &hm, const int &level, const submat_info &si, level_1s &last_level);

        /**
         * Write T_ and L_ to binary file.
         * @param hm Hash map in current level.
         * @param level Store the given level bit_vector.
         * @param filename Dst filename.
         */
        void write_to_bin(const pos_submat &hm, const int &level, const string& filename);

        /**
         * Convert hash map to bit_vector
         * @param hm
         * @param level Store the given level bit_vector.
         */
        void write_to_memory(const pos_submat &hm, const int &level);

    public:
        /**
         * Merge each level's Tl to T_.
         */
        void merge_tree_bitmap();

        /**
         * Build sdsl::rank_support_v from T_ and L_.
         */
        void build_rank_support();

        /**
         * Return true iff node p points to q and false otherwise.
         * @param p Node of start.
         * @param q Node of end.
         * @return
         */
        bool check_link(size_t p, size_t q);

        /**
         * Return children array of node p.
         * @param p
         * @return
         */
        vector<size_t> get_children(size_t p);

        /**
         * Return parents array of node q.
         * @param q
         * @return
         */
        vector<size_t> get_parents(size_t q);

        /**
         * Using the rank function from sdsl::rank_support_v.
         * rank(k) equals number of 1 in T||L[0, k]
         * @param pos Position in T||L.
         * @return Rank number of pos in T||L.
         */
        size_t rank(llong pos);

    public:

        typedef vector<submat_info > edge_array;

        void build_from_edge_array_csv(const edge_array& edges);

        /**
         * Read edge array from csv and construct k2tree and write it to binary files.
         * @param csv_name Edge array file name.
         * @param path Path to store k2tree binary files.
         * @param write_flag Determine writing T_ and L_ to binary file or to memory.
         */
        void build_from_edge_array_csv(const string &csv_name, const string &path, const int &write_flag);

    protected:
        int k1_;
        int k2_;
        int k1_levels_;
        int kL_;

        int height_;
        size_t n_prime_;

        size_t node_num_;
        size_t edge_num_;

        bit_vector T_;
        bit_vector L_;

        vector<bit_vector> tree_bitmap_;

    private:
        rank_support_v<1> t_rank;
        rank_support_v<1> l_rank;

        /**
         * Length of each level in T, aka Tl.
         */
        vector<llong> level_pos;
    };
}

#endif //K2TREE_K2TREE_H

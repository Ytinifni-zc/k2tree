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

using namespace k2tree;
using std::bitset;
using sdsl::bit_vector;
using std::unordered_map;
using std::unordered_set;

namespace k2tree {
    const int to_binary = 0x1;
    const int to_memory = 0x2;

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
         * @param edge_num_
         * @param path Path of storing k2tree binary files.
         */
        explicit k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_, const string &path);

        void T(bit_vector t);
        void L(bit_vector l);
        bit_vector T();
        bit_vector L();

    private:
        static const size_t __n = 26;
        static const size_t __p = 45;
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
        typedef unordered_set<submat_info, submat_info_hash> level_1s;

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

        size_t rank(size_t pos);

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

        size_t node_num_;
        size_t edge_num_;

        bit_vector T_;
        bit_vector L_;

        vector<bit_vector> tree_bitmap_;

    };
}

#endif //K2TREE_K2TREE_H

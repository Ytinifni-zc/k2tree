//
// Created by zhaocheng on 17-11-23.
//

#ifndef K2TREE_K2TREE_COMPRESSED_H
#define K2TREE_K2TREE_COMPRESSED_H

#include <k2tree.h>
#include <memory>
#include <fstream>
#include <compression/compressor.h>
extern "C" {
#include <dacs.h>
};

using libk2tree::compression::Vocabulary;
using libk2tree::compression::HashTable;
using std::shared_ptr;
using std::ofstream;
using std::ifstream;

namespace libk2tree {

    class k2tree_compressed: public k2tree {
    public:

        k2tree_compressed(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_,
                          const bit_vector &T_, const bit_vector &L_);


        /**
         * Read k2tree or (k2tree and compressL_) from file.
         * @param k1_
         * @param k2_
         * @param k1_levels_
         * @param kL_
         * @param node_num_
         * @param path
         * @param read_flag read_T_levels means read splited T, read_T means read T.
         * @param read_compressL false for build compressL from T and L; true for read it from file.
         */
        k2tree_compressed(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_,
                          const string &path, const int& read_flag=read_T_levels,
                          const bool& read_compressL=false
        );

        /**
         * Builds a <em>k<sup>2</sup></em>-tree with the same information but
         * compressing the leaves.
         */
        void build_compressed_leaves();

        /**
         * Builds a <em>k<sup>2</sup></em>-tree with the same information but
         * compressing the leaves using the specified vocabulary.
         *
         * @param table Hash table associating each word with their corresponding
         * frequency.
         * @param voc Word vocabulary sorted by frequency.
         */
        void build_compressed_leaves(const HashTable &table, shared_ptr<Vocabulary> voc);

        void save(const string &path);

//        /**
//         * Loads a tree from a file. If the file doesn't contain
//         * a valid representation this function yields an undefined behaviour.
//         *
//         * @param in Input stream pointing to the file storing the tree.
//         * @see k2tree_comressed::save
//         */
//        explicit k2tree_compressed(ifstream *in);
//
//        /**
//         * Creates a tree loading it from a file but using the specified vocabulary.
//         * This method is used when a series of trees share the same vocabulary.
//         *
//         * @param in Input stream pointing to the file storing the tree.
//         * @param voc Vocabulary of the leaf level.
//         * @see k2tree_compressed::save
//         */
//        void Save(ofstream *out, bool save_voc = true) const;
//
//        /**
//         * Saves the tree to a file.
//         * @param out Stream pointing to file.
//         * @param save_voc Wheter or not to save the vocabulary.
//         */
//        k2tree_compressed(ifstream *in, shared_ptr<Vocabulary> voc);
//
//        /**
//         * Returns memory usage of the structure.
//         * @return Size in bytes
//         */
//        void save(ofstream *out, bool save_voc=true) const;
//
//        size_t get_size() const;

        FTRep* compressL();

        ~k2tree_compressed() {
            destroyFT(compressL_);
        }

    private:
        /**
         * Compressed representation of the leafs using dacs.
         */
        FTRep* compressL_;
        /**
         * Pointer to vocabulary
         */
        shared_ptr<Vocabulary> voc_;

        /**
         * Returns word containing the bit at the given position
         * It access the corresponding word in the DAC.
         *
         * @param pos Position in the complete sequence of bit of the last level.
         * @return Pointer to the first position of the word.
         */
        const uchar *get_word(size_t pos) const {
            // TODO Port to 64-bits
            uint iword = accessFT(compressL_, pos/(kL_*kL_));
            return voc_->get(iword);
        }

    };

}

#endif //K2TREE_K2TREE_COMPRESSED_H

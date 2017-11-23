//
// Created by zhaocheng on 17-11-23.
//

#include <k2tree.h>
#include <k2tree_compressed.h>

k2tree_compressed::k2tree_compressed(int k1_, int k2_,
                                     int k1_levels_, int kL_,
                                     size_t node_num_, size_t edge_num_,
                                     const bit_vector &T_, const bit_vector &L_) :
        k2tree(k1_, k2_, k1_levels_, kL_,
               node_num_, edge_num_, T_, L_) {}


FTRep* libk2tree::k2tree_compressed::compressL() {
    return compressL_;
}

void k2tree_compressed::build_compressed_leaves(const HashTable &table, shared_ptr<Vocabulary> voc) {
    size_t cnt = words_cnt();
    uint size = words_size();
    uint *codewords;
    try {
        codewords = new uint[cnt];
    } catch (std::bad_alloc ba) {
        std::cerr << "[k2tree::compress_leaves] Error: " << ba.what() << std::endl;
        exit(1);
    }

    size_t i = 0;
    words([&] (const uchar *word) {
        size_t addr;
        if (!table.search(word, size, &addr)) {
            std::cerr << "[k2tree::compress_leaves] Erros: Word not found\n";
            exit(1);
        }
        codewords[i++] = table[addr].codeword;
    });

    FTRep *compressL;
    try {
        // TODO Port to 64-bits
        compressL = createFT(codewords, cnt);
    } catch (...) {
        std::cerr << "[k2tree::compress_leaves] Erros: Could not create DAC\n";
        exit(1);
    }

    delete[] codewords;

    compressL_ = compressL;
    voc_ = voc;
}


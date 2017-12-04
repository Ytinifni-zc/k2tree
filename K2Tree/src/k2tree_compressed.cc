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

k2tree_compressed::k2tree_compressed(int k1_, int k2_, int k1_levels_, int kL_,
                                     size_t node_num_, const string &path,
                                     const int &read_flag, const bool& read_compressL) :
        k2tree(k1_, k2_, k1_levels_, kL_,
               node_num_, path, read_flag) {
    if (read_compressL) {
        char *ft_path = strdup((path + "L_FTR.bin").c_str());
        compressL_ = loadFT(ft_path);
        ifstream in(path + "voc.bin", ifstream::binary);
        voc_ = std::make_shared<Vocabulary>(&in);
        in.close();
    } else {
        build_compressed_leaves();
    }
}

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

void k2tree_compressed::build_compressed_leaves() {
    compression::FreqVoc(*this, [&](const HashTable& table,
                                    shared_ptr<Vocabulary> voc) {
        this->build_compressed_leaves(table, voc);
    });
}

void k2tree_compressed::save(const string &path) {
    char * ft_path = strdup((path+"L_FTR.bin").c_str());
    saveFT(compressL_, ft_path);
    ofstream out(path+"voc.bin", ofstream::binary);
    voc_->Save(&out);
    out.close();

}

int k2tree_compressed::accessCompressL(llong pos) const {
    auto wsize = kL_*kL_;
    auto word = *(get_word(pos)+(pos%wsize)/8);
    auto pos_in_word = (pos % wsize)%8;
    return ( (word >> (pos_in_word)) & 1 );
}

bool k2tree_compressed::check_link(size_t p, size_t q) {
    return check_link_(n_prime_, --p, --q, -1, 0, [=](llong pos){return accessCompressL(pos);});
}

vector<size_t> k2tree_compressed::get_children(size_t p) {
    vector<size_t> children(0);
    get_child_(n_prime_, --p, 0, -1, 0, children, [=](llong pos){return accessCompressL(pos);});
    return children;
}

vector<size_t> k2tree_compressed::get_parents(size_t q) {
    vector<size_t> parents(0);
    get_parent_(n_prime_, 0, --q, -1, 0, parents, [=](llong pos){return accessCompressL(pos);});
    return parents;
}





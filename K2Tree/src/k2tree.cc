//
// Created by inFinity on 2017/11/7.
//
#include <k2tree.h>
#include <utils/sort.h>
#include <utils/file.h>
#include <sdsl/io.hpp>
#include <iostream>
#include <fstream>
#include <map>

using std::ifstream;
using std::ofstream;
using std::map;
using std::cout;
using std::endl;

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_) :
        k1_(k1_), k2_(k2_), k1_levels_(k1_levels_), kL_(kL_), node_num_(node_num_), edge_num_(edge_num_)
{
    set_tree_unit();
}

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_,
                       const bit_vector &T_, const bit_vector &L_) : k1_(k1_), k2_(k2_), k1_levels_(k1_levels_),
                                                                     kL_(kL_), node_num_(node_num_),
                                                                     edge_num_(edge_num_), T_(T_), L_(L_)
{
    set_tree_unit();
}

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_, size_t edge_num_,
                       const bit_vector &T_) : k1_(k1_), k2_(k2_), k1_levels_(k1_levels_),
                                                                     kL_(kL_), node_num_(node_num_),
                                                                     edge_num_(edge_num_), T_(T_)
{
    set_tree_unit();
}



void libk2tree::k2tree::set_tree_unit() {
    leaf_bits = kL_*kL_;
    submat1 = k1_*k1_;
    submat2 = k2_*k2_;

    int x = static_cast<int>(ceil(log(node_num_/pow(k1_, k1_levels_)/kL_)/log(k2_)));
    height_ = k1_levels_ + x + 1;

    tree_bitmap_.resize(height_);

}

int get_T_num(const string &path) {
    FILE *pp;
    string cmd = "ls "+path+"T*.bin | wc -l";
    pp = popen(cmd.c_str(), "r");
    int ret = 0;
    if (pp) {
        char *line;
        char buf[1000];
        line = fgets(buf, sizeof buf, pp);
        if (!line) return -1;
        ret = atoi(line);
        pclose(pp);
    }
    return ret;
}

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_,
                       size_t node_num_, const string &path, const int &read_flag) :
        k1_(k1_), k2_(k2_), k1_levels_(k1_levels_), kL_(kL_),
        node_num_(node_num_)
{
    assert(read_flag == read_T || read_flag == read_T_levels);
    set_tree_unit();
    if (read_flag == libk2tree::read_T_levels) {
        const char *l_file = (path + "L" + std::to_string(kL_) + ".bin").c_str();
        long int l_filesize = utils::get_file_size(l_file);
        int l_submat_size = get_submat_size(leaf_bits);
        cout << l_file << " " << l_filesize << " " << l_submat_size << endl;
        sdsl::load_from_file(L_, l_file);

        int level = get_T_num(path);

        vector<bit_vector> tmp_T(level);
        for (int i = 1; i <= level; ++i) {
            const char *t_file = (path + "T" + std::to_string(i) + ".bin").c_str();
            long int t_filesize = utils::get_file_size(t_file);
            int k = which_k(level);
            int submat_size = which_submat(level);
            int t_submat_size = get_submat_size(k * k);
            cout << t_file << " " << t_filesize << " " << t_submat_size << endl;

            sdsl::load_from_file(tmp_T[i - 1], t_file);
        }

        int t_size = 0;
        for (auto t: tmp_T)
            t_size += t.size();
        T_.resize(t_size);
        int idx = 0;
        for (int i = 0; i < level; ++i) {
            for (auto b: tmp_T[i]) {
                T_[idx++] = b;
            }
        }
    } else {
        string l_file = path + "L.bin";
        sdsl::load_from_file(L_, l_file);
        string t_file = path + "T.bin";
        sdsl::load_from_file(T_, t_file);
    }
    build_rank_support();
    edge_num_ = l_rank(L_.size()-1);
}

bit_vector libk2tree::k2tree::T() {
    return T_;
}

bit_vector libk2tree::k2tree::L() {
    return L_;
}

vector<bit_vector> libk2tree::k2tree::tree_bitmap() {
    return tree_bitmap_;
}

size_t k2tree::edge_num() {
    return edge_num_;
}

void libk2tree::k2tree::build_from_edge_array_csv(const edge_array &edges) {
    // TODO
}

void libk2tree::k2tree::build_from_edge_array_csv(const string &csv_f, const string &path, const int &write_flag) {
    pos_submat last_hm;
    int level = height_;

    ifstream in(csv_f, ifstream::in);
    assert(!in.fail());
    int u = 0, v = 0;
    double line_num = 0;
    level_1s last_level, last_level2;

    while (line_num < edge_num_ && !in.eof()) {

        in >> u >> v;
        u --; v--;

        hm_insert_bit(last_hm, level, u, v, last_level);
        if (!((size_t)line_num % (edge_num_/100))) {
            //fprintf(stderr, "<%d, %d>\n", u, v);
            //fprintf(stderr, "%.1f%\n", line_num/edge_num_*100);
        }
        line_num++;

    }

    in.close();

    string l_f = path + "L" + std::to_string(kL_) + ".bin";
    // TODO write_flag
    switch (write_flag) {
        case to_binary:
            write_to_bin(last_hm, level-1, l_f);
            break;
        case to_memory:
            write_to_memory(last_hm, level-1);
            break;
        default:
            write_to_memory(last_hm, level-1);
            break;
    }

    level --;
    last_hm.clear();

    bool flag = true;
    while (level) {
        std::cout << "Current_level: " << level << std::endl;

        if (flag) {
            for (auto last_pos: last_level) {
                hm_insert_bit(last_hm, level, last_pos, last_level2);
            }
            last_level.clear();
        } else {
            for (auto last_pos: last_level2) {
                hm_insert_bit(last_hm, level, last_pos, last_level);
            }
            last_level2.clear();
        }

        switch (write_flag) {
            case to_binary:
                l_f = path + "T" + std::to_string(level) + ".bin";
                write_to_bin(last_hm, level-1, l_f);
                break;
            case to_memory:
                write_to_memory(last_hm, level-1);
                break;
            default:
                write_to_memory(last_hm, level-1);
                break;
        }
        last_hm.clear();

        level --;
        flag = !flag;
    }


}

size_t libk2tree::k2tree::rank(size_t pos) {
    if (pos >= T_.size()+L_.size()) {
        std::cerr << "Position is bigger than k2tree." << std::endl;
        exit(1);
    }
    ;
    return 0;
}

void libk2tree::k2tree::hm_insert_bit(pos_submat &hm, const int &level,
                                   const submat_info &si, level_1s &last_level) {
    int k = which_k(level);
    int submat_size = which_submat(level);
    int u = si.u.to_ulong(), v = si.v.to_ulong();
    submat_pos pos = get_pos(u/k, v/k, level-1);
    bit_vector submat(submat_size, 0);
    int tmp_idx = ((u%k)*k+v%k);
    submat[tmp_idx] = 1;

    if (hm.find(pos) == hm.end()) {
        hm.insert(std::make_pair(pos, submat));
        last_level.insert(submat_info(u/k, v/k));
    } else {
        hm[pos][tmp_idx] = 1;
    }
}

void libk2tree::k2tree::hm_insert_bit(pos_submat &hm, const int &level,
                                   const int &u, const int &v, level_1s &last_level) {
    int k = which_k(level);
    int submat_size = which_submat(level);
    submat_pos pos = get_pos(u/k, v/k, level-1);
    bit_vector submat(submat_size, 0);
    int tmp_idx = ((u%k)*k+v%k);
    submat[tmp_idx] = 1;

    if (hm.find(pos) == hm.end()) {
        hm.insert(std::make_pair(pos, submat));
        last_level.insert(submat_info(u/k, v/k));
    } else {
        hm[pos][tmp_idx] = 1;
    }
}

void libk2tree::k2tree::write_to_bin(const pos_submat &hm, const int &level, const string &filename) {
    assert(level >= 0 && level < height_);
    cout << filename << endl;

    ofstream out(filename, ofstream::binary);
    write_to_memory(hm, level);
    sdsl::store_to_file(tree_bitmap_[level], filename);
    out.close();
}

void libk2tree::k2tree::write_to_memory(const pos_submat &hm, const int &level) {
    assert(level >= 0 && level < height_);
    if (tree_bitmap_[level].size() > 0)
        return;

    size_t submat_size = hm.begin()->second.size();
    tree_bitmap_[level].resize(hm.size()*submat_size);
    map<submat_pos, bit_vector, cmp_by_submat_pos> _hm(hm.begin(), hm.end());

    size_t idx = 0;
    for (auto p: _hm) {
        for (auto b: p.second) {
            tree_bitmap_[level][idx++] = b;
        }
    }
}

void libk2tree::k2tree::merge_tree_bitmap() {
    L_ = tree_bitmap_.back();
    uint64_t T_size = 0;
    for (int i = 0; i < height_-1; ++i) {
        T_size += tree_bitmap_[i].size();
    }
    T_.resize(T_size);
    int idx = 0;
    for (int i = 0; i < height_-1; ++i) {
        for (int j = 0; j < tree_bitmap_[i].size(); ++j) {
            T_[idx++] = tree_bitmap_[i][j];
        }
    }
    tree_bitmap_.clear();
    tree_bitmap_.shrink_to_fit();
}

void k2tree::build_rank_support() {
    assert(T_.size() != 0 && L_.size() != 0);
    t_rank = rank_support_v<1>(&T_);
    l_rank = rank_support_v<1>(&L_);
}


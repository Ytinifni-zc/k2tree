//
// Created by inFinity on 2017/11/7.
//
#include <k2tree.h>
#include <utils/sort.h>
#include <utils/file.h>

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

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_,
                          size_t edge_num_, const bit_vector &T_, const bit_vector &L_) :
        k1_(k1_), k2_(k2_), k1_levels_(k1_levels_),
        kL_(kL_), node_num_(node_num_),
        edge_num_(edge_num_), T_(T_), L_(L_)
{
    set_tree_unit();
}

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_, size_t node_num_,
                          size_t edge_num_, const bit_vector &T_) :
        k1_(k1_), k2_(k2_), k1_levels_(k1_levels_),
        kL_(kL_), node_num_(node_num_),
        edge_num_(edge_num_), T_(T_)
{
    set_tree_unit();
}

libk2tree::k2tree::k2tree(k2tree &&lhs): k1_(lhs.k1_),
    k2_(lhs.k2_),
    k1_levels_(lhs.k1_levels_),
    kL_(lhs.kL_),
    node_num_(lhs.node_num_),
    edge_num_(lhs.edge_num_),
    T_(lhs.T_),
    L_(lhs.L_) {}


void libk2tree::k2tree::set_tree_unit() {
    leaf_bits = kL_*kL_;
    submat1 = k1_*k1_;
    submat2 = k2_*k2_;

    int x = static_cast<int>(ceil(log(node_num_/pow(k1_, k1_levels_)/kL_)/log(k2_)));
    height_ = k1_levels_ + x + 1;
    n_prime_ = static_cast<size_t>(pow(k1_, k1_levels_) * pow(k2_, x) * kL_);

    tree_bitmap_.resize(height_);

}

libk2tree::k2tree::k2tree(int k1_, int k2_, int k1_levels_, int kL_,
                       size_t node_num_, const string &path, const int &read_flag) :
        k1_(k1_), k2_(k2_), k1_levels_(k1_levels_), kL_(kL_),
        node_num_(node_num_) {
    assert(read_flag == read_T || read_flag == read_T_levels);
    set_tree_unit();
    if (read_flag == libk2tree::read_T_levels) {
        const char *l_file = (path + "L" + std::to_string(kL_) + ".bin").c_str();
        long int l_filesize = utils::get_file_size(l_file);
        int l_submat_size = get_submat_size(leaf_bits);
        cout << l_file << " " << l_filesize << " " << l_submat_size << endl;
        sdsl::load_from_file(L_, l_file);

        int level = height_-1;

        vector<bit_vector> tmp_T(level);
        for (int i = 1; i <= level; ++i) {
            const char *t_file = (path + "T" + std::to_string(i) + ".bin").c_str();
            long int t_filesize = utils::get_file_size(t_file);
            int k = which_k(level);
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
        build_rank_support();
    } else {
        string l_file = path + "L.bin";
        sdsl::load_from_file(L_, l_file);
        string t_file = path + "T.bin";
        sdsl::load_from_file(T_, t_file);
        build_rank_support();
        split_T();
    }
    edge_num_ = l_rank(L_.size());
}

bit_vector libk2tree::k2tree::T() const {
    return T_;
}

bit_vector libk2tree::k2tree::L() const {
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
        if (edge_num_>10000 && !((size_t)line_num % (edge_num_/100))) {
            fprintf(stderr, "%.1f%\n", line_num/edge_num_*100);
        }
        line_num++;

    }

    in.close();
    std::cout << "Line number: " << static_cast<int>(line_num) << std::endl;

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
    std::cout << "tree_bitmap_[last_level].size(): ";
    auto l_size = tree_bitmap_[level-1].size();
    std::cout << l_size << std::endl;
    auto tmp = rank_support_v<1>(&tree_bitmap_[level-1]);
    std::cout << "Number of L_ 1s: " << tmp.rank(l_size) << std::endl;

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

void libk2tree::k2tree::hm_insert_bit(pos_submat &hm, const int &level,
                                   const submat_info &si, level_1s &last_level) {
    int k = which_k(level);
    int submat_size = which_submat(level);
    int u = si.u.to_ulong(), v = si.v.to_ulong();
    submat_pos pos = get_pos(u/k, v/k, level-1);
    bit_vector submat(submat_size, 0);
    int tmp_idx = ((u%k)*k+v%k);
    submat[tmp_idx] = 1;

    if (hm.end() == hm.find(pos)) {
        hm.insert(std::make_pair(pos, submat));
        last_level.push_back(submat_info(u/k, v/k));
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
        last_level.push_back(submat_info(u/k, v/k));
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
    if (0 < tree_bitmap_[level].size())
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

void k2tree::split_T() {
    level_pos.resize(height_-1);
    level_pos[0] = k1_*k1_;
    // Run start from level 2.
    int level = 2;
    int t_size = k1_*k1_;
    size_t tmp_rank = 0;
    for (; level < height_; ++level) {
        auto k = which_k(level);
        auto current_rank = rank(t_size-1);
        level_pos[level-1] = (current_rank - tmp_rank)*k*k;
        tmp_rank = current_rank;
        t_size+=level_pos[level-1];
    }
}

void k2tree::build_rank_support() {
    assert(T_.size() != 0 && L_.size() != 0);
    t_rank = rank_support_v<1>(&T_);
    l_rank = rank_support_v<1>(&L_);
}

size_t libk2tree::k2tree::rank(llong pos) {
    if (pos < 0) return 0;
    if (pos >= static_cast<llong>(T_.size()+L_.size())) {
        std::cerr << "Position is bigger than k2tree." << std::endl;
        exit(1);
    }
    pos ++;
    if (pos <= T_.size())
        return t_rank.rank(pos);
    else
        return t_rank(T_.size())+l_rank.rank(pos-T_.size());
}

bool k2tree::check_link_(size_t n, size_t p, size_t q, llong pos, int level,
                         const std::function<int(llong)> &accessL) {
    // 主要问题为在树中找叶子结点时，每一层的内部节点在T中的位置
    // 思路为：当level < k1_levels时，与论文一致，当level >= k1_levels时，
    // 记录前k1_levels-1层在T中的位置，再加上当前层中1的个数与k2^2的积，可得到
    // 孩子结点的位置，然后再根据p、q取具体在子阵中的位置。
    if (pos >= static_cast<llong>(T_.size()+L_.size())) {
        std::cerr << "Position is bigger than k2tree." << std::endl;
        exit(1);
    }
    if (pos >= static_cast<llong>(T_.size())) { // Leaf
        return 1==accessL(pos-T_.size());
    } else { //internal node
        auto k = which_k(level);
        if (pos == -1 or T_[pos] == 1) {
            if (level < k1_levels_) {
                auto y = rank(pos) * k*k;
                auto n_div_k = n/k;
                y += std::floor(static_cast<double>(p)/n_div_k)*k+
                     std::floor(static_cast<double>(q)/n_div_k);
                return check_link_(n_div_k, p%n_div_k, q%n_div_k, y, level+1, accessL);
            } else {
                auto delimiter = (level == height_-1)?level:k1_levels_;
                auto tmp_pos = 0;
                for (int i = 0; i < delimiter-1; ++i)
                    tmp_pos += level_pos[i];
                k = which_k(level+1);
                auto y = tmp_pos+level_pos[delimiter-1]+(rank(pos-1)-rank(tmp_pos-1))*k*k;
                auto n_div_k = n/k;
                y += std::floor(static_cast<double>(p)/n_div_k)*k+
                     std::floor(static_cast<double>(q)/n_div_k);
                return check_link_(n_div_k, p%n_div_k, q%n_div_k, y, level+1, accessL);
            }
        } else
            return false;
    }
}

bool k2tree::check_link(size_t p, size_t q) {
    return check_link_(n_prime_, --p, --q, -1, 0,
                       [=](llong pos){ return L_[pos]; });
}

void k2tree::get_child_(size_t n, size_t p, size_t q, llong pos, int level,
                        vector<size_t> & children, const std::function<int(llong)> &accessL) {
    if (pos >= static_cast<llong>(T_.size()+L_.size())) {
        std::cerr << "Position is bigger than k2tree." << std::endl;
        exit(1);
    }
    if (pos >= static_cast<llong>(T_.size())) { // Leaf
        if(accessL(pos-T_.size())) {
            children.push_back(++q);
        }
    } else {
        if (pos == -1 or T_[pos] == 1) {
            if (level < k1_levels_) {
                auto k = which_k(level);
                auto y = rank(pos) * k*k;
                auto n_div_k = n/k;
                y += std::floor(static_cast<double>(p)/n_div_k)*k;
                for (int j = 0; j < k; ++j) {
                    get_child_(n_div_k, p%n_div_k, q+n_div_k*j, y+j, level+1, children, accessL);
                }
            } else {
                auto delimiter = (level == height_-1)?level:k1_levels_;
                auto tmp_pos = 0;
                for (int i = 0; i < delimiter-1; ++i)
                    tmp_pos += level_pos[i];
                auto k = which_k(level+1);
                auto y = tmp_pos+level_pos[delimiter-1]+(rank(pos-1)-rank(tmp_pos-1))*k*k;
                auto n_div_k = n/k;
                y += std::floor(static_cast<double>(p)/n_div_k)*k;
                for (int j = 0; j < k; ++j) {
                    get_child_(n_div_k, p%n_div_k, q+n_div_k*j, y+j, level+1, children, accessL);
                }
            }
        }
    }
}

vector<size_t> k2tree::get_children(size_t p) {
    vector<size_t> children(0);
    get_child_(n_prime_, --p, 0, -1, 0, children,
               [=](llong pos){return L_[pos];});
    return children;
}

void k2tree::get_parent_(size_t n, size_t p, size_t q, llong pos, int level,
                         vector<size_t> &parents, const std::function<int(llong)> &accessL) {
    if (pos >= static_cast<llong>(T_.size()+L_.size())) {
        std::cerr << "Position is bigger than k2tree." << std::endl;
        exit(1);
    }
    if (pos >= static_cast<llong>(T_.size())) { // Leaf
        if(accessL(pos-T_.size())) {
            parents.push_back(++p);
        }
    } else {
        if (pos == -1 or T_[pos] == 1) {
            if (level < k1_levels_) {
                auto k = which_k(level);
                auto y = rank(pos) * k*k;
                auto n_div_k = n/k;
                y += std::floor(static_cast<double>(q)/n_div_k);
                for (int j = 0; j < k; ++j) {
                    get_parent_(n_div_k, p+n_div_k*j, q%n_div_k, y+j*k, level+1, parents, accessL);
                }
            } else {
                auto delimiter = (level == height_-1)?level:k1_levels_;
                auto tmp_pos = 0;
                for (int i = 0; i < delimiter-1; ++i)
                    tmp_pos += level_pos[i];
                auto k = which_k(level+1);
                auto y = tmp_pos+level_pos[delimiter-1]+(rank(pos-1)-rank(tmp_pos-1))*k*k;
                auto n_div_k = n/k;
                y += std::floor(static_cast<double>(q)/n_div_k);
                for (int j = 0; j < k; ++j) {
                    get_parent_(n_div_k, p+n_div_k*j, q%n_div_k, y+j*k, level+1, parents, accessL);
                }
            }
        }
    }
}

vector<size_t> k2tree::get_parents(size_t q) {
    vector<size_t> parents(0);
    get_parent_(n_prime_, 0, --q, -1, 0, parents,
                [=](llong pos){return L_[pos];});
    return parents;
}


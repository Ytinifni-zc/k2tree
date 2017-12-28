//
// Created by inFinity on 2017/11/16.
//

#include <k2tree.h>
#include <k2tree_partition.h>
#include <thread>
#include <unistd.h>
#include <utils/file.h>
#include <unordered_map>
#include <algorithm>
#include <async++.h>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;

libk2tree::k2tree_partition::k2tree_partition(int k0_, int k1_, int k2_, int k1_levels_, int kL_,
                                           size_t node_num_, size_t edge_num_) :
        k0_(k0_), k2tree(k1_, k2_, k1_levels_, kL_, node_num_, edge_num_) {
    part_tree_bitmap_.resize(k0_*k0_);
}

void libk2tree::k2tree_partition::build_partition_k2tree(vector<string> file_list, string store_path) {
    int k0_square = file_list.size();
    assert(k0_square == k0_*k0_);

    int core_num = sysconf(_SC_NPROCESSORS_CONF) - 2;

    vector<vector<int>> t_indice(core_num);
    unordered_map<int, long int> index_filesize;
    for (int i = 0; i < k0_square; ++i) {
        index_filesize.insert(std::make_pair(i, libk2tree::utils::get_file_size(file_list[i].c_str())));
    }
    vector<pair<int, long int>> elems(index_filesize.begin(), index_filesize.end());
    std::sort(elems.begin(), elems.end(),
              [=](pair<int, long int> a, pair<int, long int> b){
        return a.second > b.second;
    });

    for (int i = 0; i < elems.size(); ++i) {
        t_indice[i%core_num].push_back(elems[i].first);
    }

    /*
    for (auto t: t_indice) {
        for (auto i: t) {
            cout << "<" << i << ", " << index_filesize[i] << ">" << endl;
        }
    }
     */

    auto build_partition_k2tree = [=](vector<int> file_indice) {
        for (auto i : file_indice) {
            string file = file_list[i];
            libk2tree::k2tree tree(k1_, k2_, k1_levels_, kL_, node_num_, edge_num_);
            cout << file << endl;
            tree.build_from_edge_array_csv(file, "", libk2tree::to_memory);
            part_tree_bitmap_[i] = tree.tree_bitmap();
        }
    };

    std::thread *threads[core_num];
    for (int i = 0; i < core_num; ++i) {
        threads[i] = new std::thread( build_partition_k2tree, t_indice[i] );
    }

    for (int i = 0; i < core_num; ++i) {
        threads[i]->join();
    }

    merge_part_tree_bitmap();

    for (auto t: threads)
        delete t;

    sdsl::store_to_file(T_, store_path+"T.bin");
    sdsl::store_to_file(L_, store_path+"L.bin");
}

void libk2tree::k2tree_partition::merge_part_tree_bitmap() {
    auto k0_square = k0_*k0_;
    uint64_t T_size = k0_square, L_size = 0;
    for (int i = 0; i < k0_square; ++i) {
        uint64_t tmp_size = part_tree_bitmap_[i].size();
        for (int j = 0; j < tmp_size; ++j) {
            if (j != tmp_size-1)
                T_size += part_tree_bitmap_[i][j].size();
            else
                L_size += part_tree_bitmap_[i][j].size();
        }
    }

    T_.resize(T_size);
    L_.resize(L_size);

    uint64_t t_idx = k0_square, l_idx = 0;
    for (int i = 0; i < k0_square; ++i) {
        uint64_t tmp_size = part_tree_bitmap_[i].size();
        for (int j = 0; j < tmp_size; ++j) {
            if (j == tmp_size-1)
                T_[i] = part_tree_bitmap_[i][j].empty()?0:1;
            for (int k = 0; k < part_tree_bitmap_[i][j].size(); ++k) {

                if (j != tmp_size-1)
                    T_[t_idx++] = part_tree_bitmap_[i][j][k];
                else
                    L_[l_idx++] = part_tree_bitmap_[i][j][k];

            }
        }
    }

    part_tree_bitmap_.clear();
    part_tree_bitmap_.shrink_to_fit();

}

libk2tree::k2tree_edge_partition::k2tree_edge_partition(int k0, vector<config> configures):
    k0_(k0), configures_(configures) {
    assert(configures.size() == k0*k0);
    k2tree_parts.resize(k0_*k0_);
    for (int i = 0; i < k0*k0; ++i) {
        k2tree_parts[i] = std::make_shared<k2tree>(
                std::get<0>(configures[i]),
                std::get<1>(configures[i]),
                std::get<2>(configures[i]),
                std::get<3>(configures[i]),
                std::get<4>(configures[i]),
                std::get<5>(configures[i])
        );
    }
}

libk2tree::k2tree_edge_partition::k2tree_edge_partition(int k0, vector<config> configures, vector<shared_ptr<k2tree>> kp)
    :k0_(k0), configures_(configures), k2tree_parts(kp) {
}


void libk2tree::k2tree_edge_partition::build_from_edge_arrays(vector<int(*)[2]> edge_lists,
        vector<uint64_t> size_list) {
    assert(edge_lists.size() == k0_*k0_);
    assert(size_list.size() == k0_*k0_);
    /*
    for (int i = 0; i < k0_*k0_; ++i) {
        std::cerr << "=========build " << i << "=========";
        k2tree_parts[i]->build_from_edge_array_csv(edge_lists[i], size_list[i]);
    }
    */
    async::parallel_for(async::irange(0, k0_*k0_), [&](int i){
        std::cerr << "=========build " << i << "=========" << std::endl;
        k2tree_parts[i]->build_from_edge_array_csv(edge_lists[i], size_list[i]);
    });
}

vector<size_t> libk2tree::k2tree_edge_partition::get_children(size_t p) {
    vector<size_t> ret;
    vector<vector<size_t>> rets;
    rets.resize(k0_);
    auto cell = std::get<4>(configures_.front());
    auto row = p/cell;
    auto part_pos = (p-1)%cell+1; // Start from 1.
    async::parallel_for(async::irange(row*k0_, (row+1)*k0_), [&](int i) {
        rets[i-row*k0_] = k2tree_parts[i]->get_children(part_pos);
    });

    for (int i = 0; i < k0_; ++i) {
        for (int j = 0; j < rets[i].size(); ++j) {
            rets[i][j] += cell*i;
        }
        ret.insert(ret.end(), rets[i].begin(), rets[i].end());
    }
    return ret;
}

void libk2tree::k2tree_edge_partition::save(std::string path) {
    std::ofstream out(path+"configure", std::ofstream::binary);
    out.write((char*)&k0_, sizeof(k0_));
    for (auto c: configures_)
        out.write((char*)&c, sizeof(c));
    out.close();

    for (int i = 0; i < k2tree_parts.size(); ++i) {
        sdsl::store_to_file(k2tree_parts[i]->T(), path+"T"+std::to_string(i)+".bin");
        sdsl::store_to_file(k2tree_parts[i]->L(), path+"L"+std::to_string(i)+".bin");
    }
}

libk2tree::k2tree_edge_partition::k2tree_edge_partition(const std::string &path) {
    auto config_filename = path+"configure";
    std::ifstream in(config_filename, std::ifstream::binary);
    in.read((char*)&k0_, sizeof(k0_));
    configures_.resize(k0_*k0_);
    k2tree_parts.resize(k0_*k0_);

    for (int i = 0; i < k0_*k0_; ++i) {
        in.read((char*)&configures_[i], sizeof(configures_[i]));
        k2tree_parts[i] = std::make_shared<k2tree>(
            std::get<0>(configures_[i]),
            std::get<1>(configures_[i]),
            std::get<2>(configures_[i]),
            std::get<3>(configures_[i]),
            std::get<4>(configures_[i]),
            std::get<5>(configures_[i])
        );
        sdsl::load_from_file(k2tree_parts[i]->T_, path+"T"+std::to_string(i)+".bin");
        sdsl::load_from_file(k2tree_parts[i]->L_, path+"L"+std::to_string(i)+".bin");
        k2tree_parts[i]->build_rank_support();
        k2tree_parts[i]->split_T();
    }
    in.close();
}

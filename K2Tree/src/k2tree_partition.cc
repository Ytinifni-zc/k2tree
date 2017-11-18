//
// Created by inFinity on 2017/11/16.
//

#include <k2tree.h>
#include <k2tree_partition.h>
#include <thread>
#include <unistd.h>

using std::cout;
using std::endl;

libk2tree::k2tree_partition::k2tree_partition(int k0_, int k1_, int k2_, int k1_levels_, int kL_,
                                           size_t node_num_, size_t edge_num_) :
        k0_(k0_), k2tree(k1_, k2_, k1_levels_, kL_, node_num_, edge_num_) {
    part_tree_bitmap_.resize(k0_*k0_);
}

void libk2tree::k2tree_partition::build_partition_k2tree(vector<string> file_list, string store_path) {
    int files_size = file_list.size();
    assert(files_size == k0_*k0_);

    long core_num = sysconf(_SC_NPROCESSORS_CONF) - 2;

    auto build_k2tree = [=](vector<int> file_indice) {
        for (auto i : file_indice) {
            string file = file_list[i];
            libk2tree::k2tree tree(k1_, k2_, k1_levels_, kL_, node_num_, edge_num_);
            cout << file << endl;
            tree.build_from_edge_array_csv(file, "", libk2tree::to_memory);
            part_tree_bitmap_[i] = tree.tree_bitmap();
        }
    };

    vector<vector<int>> t_indice(core_num);
    for (int i = 0; i < files_size; ++i) {
        t_indice[i%core_num].push_back(i);
    }

    std::thread *threads[core_num];
    for (int i = 0; i < core_num; ++i) {
        threads[i] = new std::thread( build_k2tree, t_indice[i] );
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
    uint64_t T_size = 0, L_size = 0;
    for (int i = 0; i < k0_*k0_; ++i) {
        uint64_t tmp_size = part_tree_bitmap_[i].size();
        for (int j = 0; j < tmp_size; ++j) {
            if (j != tmp_size-1) T_size += part_tree_bitmap_[i][j].size();
            else L_size += part_tree_bitmap_[i][j].size();
        }
    }

    T_.resize(T_size);
    L_.resize(L_size);

    uint64_t t_idx = 0, l_idx = 0;
    for (int i = 0; i < k0_*k0_; ++i) {
        uint64_t tmp_size = part_tree_bitmap_[i].size();
        for (int j = 0; j < tmp_size; ++j) {
            for (int k = 0; k < part_tree_bitmap_[i][j].size(); ++k) {

                if (j != tmp_size-1) T_[t_idx++] = part_tree_bitmap_[i][j][k];
                else L_[l_idx++] = part_tree_bitmap_[i][j][k];

            }
        }
    }

    part_tree_bitmap_.clear();
    part_tree_bitmap_.shrink_to_fit();

}

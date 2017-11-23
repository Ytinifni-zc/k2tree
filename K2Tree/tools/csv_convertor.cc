//
// Created by inFinity on 2017/11/7.
//

#include <k2tree.h>
#include <cstdlib>
#include <utils/time.h>
#include <iostream>
#include <utils/time.cc>
#include <utils/bit_vector.h>
#include "config.h"

int main(int argc, char** argv) {

    string path;
    string filename;
    size_t node_num, edge_num;
    int k1, k2, k1_levels, kL;

    std::tie(path, filename, node_num, edge_num, k1, k2, k1_levels, kL) =
            get_args(argc, argv);

    auto build_tree = [=]() {
        libk2tree::k2tree tree(k1, k2, k1_levels, kL, node_num, edge_num);
        tree.build_from_edge_array_csv(filename, "", libk2tree::to_memory);
        tree.merge_tree_bitmap();
        sdsl::store_to_file(tree.T(), path+"T.bin");
        sdsl::store_to_file(tree.L(), path+"L.bin");
        sdsl::sd_vector<> sd_t = tree.T();
        sdsl::sd_vector<> sd_l = tree.L();
        sdsl::store_to_file(sd_t, path+"T_sd.bin");
        sdsl::store_to_file(sd_l, path+"L_sd.bin");
        sdsl::rrr_vector<> rrr_t(tree.T());
        sdsl::rrr_vector<> rrr_l(tree.L());
        sdsl::store_to_file(rrr_t, path+"T_rrr.bin");
        sdsl::store_to_file(rrr_l, path+"L_rrr.bin");

        FTRep* listRep;
        //libk2tree::utils::bit_vector2FTRep(tree.L(), kL*kL, listRep);
        libk2tree::utils::bit_vector2int_bin(tree.L(), kL*kL, path+"L_int.bin");
        const char * ft_path = (path + "L_FTR.bin").c_str();
        //saveFT(listRep, const_cast<char *>(ft_path));

    };
    libk2tree::utils::cost(build_tree);
    return 0;

}
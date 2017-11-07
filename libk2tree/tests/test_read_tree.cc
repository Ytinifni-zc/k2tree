#include <gtest/gtest.h>
#include <dirent.h>
#include "build_tree.h"

unsigned long get_file_size(const char *path) {
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
        return filesize;
    else
        filesize = statbuff.st_size;
    return filesize;
}

void build_tree_from_bin(const string &path, vector<submat> &T, vector<leaf_bits> &L) {
    const char* l_file = (path + "L" + std::to_string(kL) + ".bin").c_str();
    int l_filesize = get_file_size(l_file);
    int l_submat_size = get_submat_size(kL*kL);
    cout << l_file << " " << l_filesize << " " << l_submat_size << endl;
    L.resize(l_filesize/l_submat_size);
    leaf_bits tmp;

    ifstream fin(l_file, ifstream::binary);
    for (int i = 0; i < l_filesize/l_submat_size; ++i) {
        fin.read((char*)&tmp, l_submat_size);
        L[i] = tmp;
    }
    fin.close();

    for (int i = 1; i <= level; ++i) {
        const char* t_file = (path + "T" + std::to_string(i) + ".bin").c_str();
        int t_filesize = get_file_size(t_file);
        int t_submat_size = get_submat_size(k*k);
        cout << t_file << " " << t_filesize << " " << t_submat_size << endl;
        ifstream fin(t_file, ifstream::binary);

        submat tmp;
        for (int j = 0; j < t_filesize/t_submat_size; ++j) {
            fin.read((char*)&tmp, t_submat_size);
            T.push_back(tmp);
        }

        fin.close();

    }
}

TEST(Read, read_tree) {

    const string path = "./k2tree/";
    //const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/";
    const string filename = path + "test.csv";
    const size_t node_num = 11, edge_num = 11;
    //const size_t node_num = 41652230, edge_num = 1468365182;

    vector<submat> T;
    vector<leaf_bits> L;

    build_tree_from_bin(path, T, L);

    for (auto t : T) {
        cout << t.to_string() << " ";
    }
    cout << endl;
    for (auto l : L) {
        cout << l.to_string() << " ";
    }
    cout << endl;
}

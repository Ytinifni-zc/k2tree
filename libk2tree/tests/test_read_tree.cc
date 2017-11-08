#include <gtest/gtest.h>
#include "build_tree.h"

vector<submat> T;
vector<leaf_bits> L;

unsigned long get_file_size(const char *path) {
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
        return filesize;
    else
        filesize = statbuff.st_size;
    return filesize;
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

    int level = get_T_num(path);

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
    build_tree_from_bin(path, T, L);
    ASSERT_NE(T.size(), 0);
    ASSERT_NE(L.size(), 0);
    cout << T.capacity()*T[0].size() << "B" << endl;
    cout << L.capacity()*L[0].size() << "B" << endl;
}

/*
TEST(Read, print_T_L) {
    for (auto t : T) {
        cout << t.to_string() << " ";
    }
    cout << endl;
    for (auto l : L) {
        cout << l.to_string() << " ";
    }
    cout << endl;
}
 */

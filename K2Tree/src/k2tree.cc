//
// Created by inFinity on 2017/11/7.
//
#include <k2tree.h>
#include <sys/stat.h>
#include <iostream>

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

k2tree::k2tree::k2tree(const vector<size_t> &ks_, const vector<submat> &T_, const vector<leaf_bits> &L_) : ks_(ks_), T_(T_), L_(L_) {}

k2tree::k2tree::k2tree(const string &path) {
    const char* l_file = (path + "L" + std::to_string(kL) + ".bin").c_str();
    int l_filesize = get_file_size(l_file);
    int l_submat_size = get_submat_size(kL*kL);
    cout << l_file << " " << l_filesize << " " << l_submat_size << endl;
    L_.resize(l_filesize/l_submat_size);
    leaf_bits tmp;

    ifstream fin(l_file, ifstream::binary);
    for (int i = 0; i < l_filesize/l_submat_size; ++i) {
        fin.read((char*)&tmp, l_submat_size);
        L_[i] = tmp;
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
            T_.push_back(tmp);
        }

        fin.close();

    }
}

vector<submat> k2tree::k2tree::T() {
    return T_;
}

vector<leaf_bits> k2tree::k2tree::L() {
    return L_;
}

size_t k2tree::k2tree::rank(size_t pos) {
    if (pos >= T_.size()+L_.size()) {
        std::cerr << "Position is bigger than k2tree." << std::endl;
        exit(1);
    }
    ;
    return 0;
}

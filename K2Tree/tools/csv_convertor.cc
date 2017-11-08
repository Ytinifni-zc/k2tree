//
// Created by inFinity on 2017/11/7.
//

#include <build_tree.h>
#include <utils/time.h>

vector<int> k_level;

submat_pos get_pos(const int &u, const int &v, const int &level) {
    if (level < 1) return submat_pos(0);
    int k = k_level[level-1];
    if (level == 1) return submat_pos(u%k*k+v%k);
    /*
    struct pos_info pre_pos_info(u/k, v/k, level-1);
    if (pre_pos_map.find(pre_pos_info) == pre_pos_map.end()) {
        pre_pos_map.insert(std::make_pair(
                pre_pos_info,
                get_pos(u / k, v / k, level - 1)
        ));
    }
    int pre_pos = pre_pos_map[pre_pos_info].to_ulong();
    */
    int pre_pos = get_pos(u/k, v/k, level - 1).to_ulong();
    return submat_pos(
            (pre_pos)*k*k+((u%k)*k+v%k)
    );
}

template<class T>
void hm_insert_bit(unordered_map<submat_pos, T> &hm, const size_t &n, const int &level, const int &u, const int &v, level_1s &last_level) {
    int k = k_level[level-1];
    submat_pos pos = get_pos(u/k, v/k, level-1);//(u/k)*(n/k) + v/k;
    T onehot = T(1)<<(k*k-1-((u%k)*k + v%k));

    if (hm.find(pos) == hm.end()) {
        hm.insert(std::make_pair(pos, onehot));
        last_level.insert(submat_info(u/k, v/k));
    }
    else
        hm[pos] |= onehot;
}

template<class T>
void write_to_bin(unordered_map<submat_pos, T> hm, const string& filename) {
    struct cmp_by_submat_pos {
        bool operator() (const submat_pos &k1, const submat_pos &k2) {
            return k1.to_ulong() < k2.to_ulong();
        }
    };
    map<submat_pos, T, cmp_by_submat_pos> _hm(hm.begin(), hm.end());

    ofstream out(filename, ofstream::binary);

    for (auto p: _hm) {
        int size = get_submat_size(p.second.size());
        out.write((char*) &p.second, size);
    }
    out.close();
}

void build_last_level_from_csv(const string& filename, const size_t & node_num, const size_t & edge_num, const string &path, level_1s &last_level) {
    // TODO
    // 先把T、L写文件
    //const size_t bits = (size_t) ceil(log2(node_num));
    //typedef bitset<bits> leaf;
    //const int leaf_size = (int)ceil(((double)bits)/8);
    //const int leaf_bits_size = (int)ceil(((double)(kL*kL))/8);
    leaves last_hm;
    int level = ceil(log(ceil(((double)node_num)/kL))/log(k))+1;
    for (int i = 0; i < level-1; ++i)
        k_level.push_back((int)k);
    k_level.push_back((int)kL);

    ifstream in(filename, ifstream::in);
    assert(!in.fail());
    int u = 0, v = 0;
    submat_pos pos = 0;
    leaf_bits onehot = 0;
    size_t n_prime = (size_t) ceil((double)node_num/kL)*kL;
    double line_num = 0;

    while (line_num <= edge_num) {

        in >> u >> v;
        u --;
        v --;

        hm_insert_bit<leaf_bits>(last_hm, n_prime, level, u, v, last_level);
        if (!((size_t)line_num % 1000000)) {
            fprintf(stderr, "<%d, %d>\n", u, v);
            fprintf(stderr, "%.2f%\n", line_num/edge_num*100);
        }
        line_num++;

    }

    in.close();

    string l_filename = path + "L" + std::to_string(kL) + ".bin";
    printf("%s\n", l_filename.c_str());
    write_to_bin<leaf_bits>(last_hm, l_filename);
}

void build_internal(const size_t & node_num, const string &path, level_1s &last_level) {

    int current_level = ceil(log(ceil(((double)node_num)/kL))/log(k));
    //int current_k = k;

    // Internal submatrix size = k*k.
    in_nodes t_hm;
    size_t current_pos = 0;
    submat current_onehot;
    int u = 0, v = 0;
    size_t n_prime = (size_t) ceil((double)node_num/kL)*kL;
    int flag = true;
    level_1s last_level2;

    while (current_level) {
        printf("Current_level: %d\n", current_level);

        n_prime = ceil((double)n_prime/k)*k;

        if (flag) {
            for (auto last_pos : last_level) {
                u = (int) last_pos.u.to_ulong();
                v = (int) last_pos.v.to_ulong();
                //cout << "<" << u << ", " << v << ">" << endl;

                hm_insert_bit<submat>(t_hm, n_prime, current_level, u, v, last_level2);
            }

            last_level.clear();
        } else {
            for (auto last_pos : last_level2) {
                u = (int) last_pos.u.to_ulong();
                v = (int) last_pos.v.to_ulong();
                //cout << "<" << u << ", " << v << ">" << endl;

                hm_insert_bit<submat>(t_hm, n_prime, current_level, u, v, last_level);
            }

            last_level2.clear();
        }

        string t_filename = path + "T" + std::to_string(current_level) + ".bin";
        write_to_bin<submat>(t_hm, t_filename);
        t_hm.clear();

        current_level --;
        flag = !flag;
    }

}

int main() {
    auto build_tree = []() {
        level_1s last_level;
        build_last_level_from_csv(filename, node_num, edge_num, path, last_level);
        build_internal(node_num, path, last_level);
    };
    k2tree::utils::cost(build_tree);
    return 0;

}
//
// Created by inFinity on 2017/11/8.
//

#include <utils/time.h>
#include <cassert>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <utils/time.cc>

using namespace std;

//        const string path = "./k2tree/";
const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/csr/";
//        const string filename = path + "../test.csv";
const string filename = path + "../twitter-2010.csv";
//        const size_t node_num = 11, edge_num = 11;
const size_t node_num = 41652230, edge_num = 1468365182;

void build_csr_from_csv() {
    const size_t bits = (size_t)ceil(log2((double)node_num));
    const int nodes_size = ceil(((double)bits)/8*8);
    typedef bitset<bits> nodes;
    vector<nodes> IA(node_num+1, 0);
    vector<nodes> JA(edge_num, 0);

    ifstream in(filename, ifstream::in);
    assert(!in.fail());

    double line_num = 0;
    int u = 0, v = 0;
    while (line_num <= edge_num) {

        in >> u >> v;
        IA[u] = nodes(IA[u].to_ulong()+1);
        JA[line_num] = nodes(v-1);

        if (!((size_t)line_num % 1000000)) {
            printf("<%d, %d>\n", u, v);
            printf("%.2f%\n", line_num/edge_num*100);
        }

        ++line_num;

    }

    in.close();

    auto write_array = [=](string filename, vector<nodes> array){

        ofstream out(filename, ofstream::binary);

        for (auto ia : array) {
            out.write((char*) &ia, nodes_size);
        }

        out.close();

    };

    string IA_filename = path + "IA.bin";
    string JA_filename = path + "JA.bin";

    write_array(IA_filename, IA);
    write_array(JA_filename, JA);

}

int main() {
    auto tmp = [](){
        build_csr_from_csv();
    };
    k2tree::utils::cost(tmp);
    return 0;
}
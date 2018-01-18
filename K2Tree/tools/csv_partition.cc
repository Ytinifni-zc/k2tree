//
// Created by inFinity on 2017/11/16.
//
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <utils/time.h>
#include <utils/time.cc>
#include <cstdio>
#include <k2tree.h>
#include "config.h"

using namespace std;

int main(int argc, char** argv) {

    const short __k0 = 128;

    string path, filename, out_file;
    size_t node_num, edge_num;
    int k0;
    if (argc <= 2) {
        path = TWITTER_PATH + "../partition/";
        filename = TWITTER_FILE;
        out_file = path + "twitter";
        node_num = TWITTER_NODE_NUM;
        edge_num = TWITTER_EDGE_NUM;
        k0 = (argc == 1)?__k0:atoi(argv[1]);
    } else {
        path = string(argv[1]);
        filename = string(argv[2]);
        out_file = string(argv[3]);
        node_num = atoi(argv[4]);
        edge_num = atoi(argv[5]);
        k0 = atoi(argv[6]);
    }

    auto part = [=]() {
        ifstream fin(filename, ifstream::in);
        assert(!fin.fail());
        vector<ofstream> fouts(k0 * k0);
        vector<int> fouts_line_num(k0 * k0, 0);

        for (int i = 0; i < k0; ++i) {
            string of = out_file + std::to_string(i) + ".bin";
            fouts[i].open(of, ofstream::binary);
            assert(!fouts[i].fail());
        }

        int u, v;
        double line_num = 0;
        auto cell = static_cast<int>(ceil(
                static_cast<double>(node_num) / k0)
        );

        int last_block_row = 0;
        while (line_num < edge_num && !fin.eof()) {

            fin >> u >> v;
            if (u == 3 && v == 0) continue;
            u--;
            v--;

            int idx = u / cell * k0 + v / cell;
            int new_u = u % cell + 1;
            int new_v = v % cell + 1;

            if (u / cell != last_block_row) {
                cout << u / cell << endl;
                for (int i = last_block_row * k0; i < u / cell * k0; ++i) {
                    fouts[i].close();
                    if (i + k0 < k0 * k0) {
                        string of = out_file + std::to_string(i + k0) + ".bin";
                        fouts[i + k0].open(of, std::ios::out);
                        assert(!fouts[i + k0].fail());
                    }
                }
            }
            last_block_row = u / cell;

            //fouts[idx] << new_u << "\t" << new_v << endl;
            fouts[idx].write((char*)&new_u, sizeof(new_u));
            fouts[idx].write((char*)&new_v, sizeof(new_v));
            fouts_line_num[idx]++;

            if (!((size_t) line_num % 1000000)) {
                //fprintf(stderr, "<%d, %d>\n", u, v);
                //fprintf(stderr, "%.2f%\n", line_num/edge_num*100);
            }
            line_num++;

        }

        for (int i = k0 * (k0 - 1); i < k0 * k0; ++i)
            fouts[i].close();
        fin.close();

    };

    auto part_from_bin = [=]() {
        int (*data)[2];
        long cnt = 0;
        utils::cost([&](){
            std::cerr << "Load edge array from bin: ";
            std::string filename = TWITTER_PATH + "../twitter-2010-2.bin";
            std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
            long fileSize = in.tellg();
            int fd = open(filename.c_str(), O_RDONLY, 0);
            if (fd == -1) {
                perror("open failed.");
                exit(1);
            }
            void* ptr = mmap(0, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
            if (ptr == MAP_FAILED) {
                perror("mmap failed.");
                exit(1);
            }
            data = static_cast<int(*)[2]>(ptr);

            cnt = fileSize / 8;
            close(fd);
            in.close();
        });
        std::cerr << "Count of twitter: " << cnt << endl;

        int k0 = 128;
        auto cell = static_cast<int>(ceil(
                static_cast<double>(node_num) / k0)
        );
        vector<vector<pair<int, int>>> part_array;
        part_array.resize(k0*k0);
        for (int i = 0; i < cnt; ++i) {
            auto u = data[i][0] - 1, v = data[i][1] -1;
            if (u == 2 && v == -1) continue;
            auto part = u/cell*k0+v/cell;
            part_array[part].push_back({u%cell+1, v%cell+1});
        }

        for (int i = 0; i < k0*k0; ++i) {
            string of = out_file + std::to_string(i) + ".bin";
            ofstream out(of, ofstream::binary);
            for (auto p: part_array[i]) {
                out.write((char*)&p.first, sizeof(p.first));
                out.write((char*)&p.second, sizeof(p.second));
            }
            out.close();
        }
    };

    libk2tree::utils::cost(part);
    //libk2tree::utils::cost(part_from_bin);
    return 0;
}

//
// Created by inFinity on 2017/11/13.
//

#include <utils/bit_vector.h>
#include <cassert>
#include <fstream>

bit_vector libk2tree::utils::int2bit_vector(const unsigned long long &num, const int &size) {
    assert (num < (1l<<size));
    bit_vector bv(size, 0);
    unsigned long long tmp = num;
    for (int i = 1; tmp != 0; i++, tmp >>= 1) {
        bv[size-i] = tmp&1;
    }
    return bv;
}

unsigned long long libk2tree::utils::bit_vector2int(const bit_vector &bv) {
    unsigned long long ret = 0;
    for (size_t i = 0; i < bv.size(); ++i) {
        ret <<= 1;
        ret |= bv[i];
    }
    return ret;
}

vector<bool> libk2tree::utils::bit_vector2vector_bool(const bit_vector &bv) {
    const size_t size = bv.size();
    vector<bool> ret(size, false);
    for (size_t i = 0; i < size; ++i) {
        ret[i] = (bv[i] == 1);
    }
    return ret;
}

unsigned long long libk2tree::utils::vector_bool2int(const vector<bool> &vb) {
    unsigned long long ret = 0;
    for (auto i : vb) {
        ret <<= 1;
        ret |= i?1:0;
    }
    return ret;
}

vector<bool> libk2tree::utils::int2vector_bool(const unsigned long long &num, const int &size) {
    assert (num < (1l<<size));
    vector<bool> vb(size, false);
    unsigned long long tmp = num;
    for (int i = 1; tmp != 0; i++, tmp>>=1) {
        vb[size-i] = tmp&1;
    }
    return vb;
}

void libk2tree::utils::int2vector_bool(const unsigned long long &num, const int &size, vector<bool> &vb) {
    assert (num < (1l<<size));
    vb.resize(size, false);
    unsigned long long tmp = num;
    for (int i = 1; tmp != 0; i++, tmp>>=1) {
        vb[size-i] = tmp&1;
    }
}

bool libk2tree::utils::store_to_file(const bit_vector& v, const std::string& file, bool is_append) {
    auto flag = std::ios::binary | std::ios::out;
    flag = (is_append) ? (flag | std::ios::app) : (flag | std::ios::trunc);
    osfstream out(file, flag);
    if (!out) {
        std::cerr<<"ERROR: util::store_to_file:: Could not open file `"<<file<<"`"<<std::endl;
        return false;
    } else {
        if (sdsl::util::verbose) {
            std::cerr<<"INFO: store_to_file: `"<<file<<"`"<<std::endl;
        }
    }
    v.serialize(out, nullptr, "", false);
    out.close();
    return true;
}

vector<uint> libk2tree::utils::bit_vector2FTRep(const bit_vector &bv, const int &unit, FTRep *&ret) {
    //assert(unit == 16 || unit == 64 || unit == 256);
    const int uint_s = sizeof(uint)*8;
    uint list_size = static_cast<uint>(
            ceil(static_cast<float>(bv.size())/uint_s)
    );
    uint* list = (uint*)malloc(sizeof(uint)*list_size);
    memset(list, 0u, list_size*sizeof(uint));
    for (int i = 0; i < bv.size(); ++i) {
        int idx = i/uint_s, bit_pos = i%uint_s;
        if (bv[i])
            *(list+idx) |= (1<<bit_pos);
    }
    ret = createFT(list, list_size);
    vector<uint> tmp(list_size);
    for (int i = 0; i < list_size; ++i) tmp[i] = *(list+i);
    return tmp;

}

void ::libk2tree::utils::bit_vector2int_bin(const bit_vector &bv, const int &unit, std::string file) {

    const int uint_s = sizeof(uint)*8;
    uint list_size = static_cast<uint>(
            ceil(static_cast<float>(bv.size())/uint_s)
    );
    uint* list = (uint*)malloc(sizeof(uint)*list_size);
    memset(list, 0, list_size*sizeof(uint));
    for (int i = 0; i < bv.size(); ++i) {
        int idx = i/uint_s, bit_pos = i%uint_s;
        if (bv[i])
            *(list+idx) |= (1<<bit_pos);
    }
    std::ofstream out(file, std::ios::binary);
    for (int i = 0; i < list_size; ++i)
        out.write((char*)(list+i), sizeof(uint));
    out.close();
}

//
// Created by inFinity on 2017/11/12.
//

#ifndef K2TREE_UTILS_BIT_VECTOR_H
#define K2TREE_UTILS_BIT_VECTOR_H

#include <sdsl/bit_vectors.hpp>
#include <sdsl/io.hpp>
#include <sdsl/sfstream.hpp>
#include <string>
#include <vector>

extern "C" {
#include <dacs.h>
};

using sdsl::bit_vector;
using sdsl::osfstream;
using std::vector;

namespace libk2tree {
    namespace utils {
        /**
         * Build bit_vector from a integer value.
         * @param num the integer value.
         * @param size size of bit_vector.
         * @return result.
         */
        bit_vector int2bit_vector(const unsigned long long &num, const int &size);

        unsigned long long bit_vector2int(const bit_vector &bv);

        vector<bool> bit_vector2vector_bool(const bit_vector &bv);

        unsigned long long vector_bool2int(const vector<bool> &vb);

        vector<bool> int2vector_bool(const unsigned long long &num, const int &size);
        void int2vector_bool(const unsigned long long &num, const int &size, vector<bool> &vb);

        bool store_to_file(const bit_vector& bv, const std::string& file, bool is_append=false);

        /**
         * Convert bit_vector to FTRep in dac.
         * @param bv L in k2tree.
         * @param unit kL*kL in the leaves level, which is chosen from {16, 64, 256}
         * @param ret Result.
         * @return Vector of uint list.
         */
        vector<uint> bit_vector2FTRep(const bit_vector& bv, const int &unit, FTRep* &ret);

        void bit_vector2int_bin(const bit_vector& bv, const int &unit, std::string file);

    }
}

#endif //K2TREE_UTILS_BIT_VECTOR_H

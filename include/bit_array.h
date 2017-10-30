#ifndef INCLUDE_BIT_ARRAY_H_
#define INCLUDE_BIT_ARRAY_H_

#include <base.h>
#include <vector>

using ::std::vector;

namespace k2tree {

    class bit_array {
    public: 
        bit_array();
        bit_array(bit_array* ba);

        size_t length();
        vector<unlong > bits();
        unlong current_bits();

        uchar get_bit(size_t pos);
        void add_bit(uchar bit);
        void add_bits(bit_array ba);
        void set_bit(size_t pos, uchar bit);

        bool is_equal_0();
        // Rank of pos in bit_array.
        size_t rank(size_t pos);

        // Release bit_array's memory.
        void clear();

        // test
        void show_bit();

    private:
        size_t length_;
        vector<unlong > bits_;
    };
}

#endif

#include <bit_array.h>
#include <gtest/gtest.h>

using k2tree::bit_array;
using k2tree::unlong;
using k2tree::uchar;

TEST(BitArray, AddBit) {
    bit_array ba;
    unlong t = 0xdeadcafedeadcafeul;
    unlong l = 0xfacebeedfacebeedul;
    for(int i = 0; i < 64; ++i){
        uchar bit = (t&(1ull << 63))>>63;
        ba.add_bit(bit);
        t <<= 1;
    }
    for(int i = 0; i < 64; ++i){
        uchar bit = (l&(1ull << 63))>>63;
        ba.add_bit(bit);
        l <<= 1;
    }
    ASSERT_EQ(ba.length(), 128);
    ba.show_bit();
    uchar tmp = 0;
    for(int i = 0; i < ba.length(); ++i) {
        tmp <<= 1;
        tmp |= ba.get_bit(i);
        if ((i+1)%4==0) {
            printf("%x", tmp);
            tmp = 0;
        }
    }
    printf("\n");
    bit_array bb;
    bb.show_bit();
    bb.add_bits(ba);
    bb.show_bit();
}

TEST(BitArray, AddBit2) {
    bit_array ba;
    unlong t = 0xdeadcafedeadul;
    unlong l = 0xfacebeedfaceul;
    for(int i = 0; i < 48; ++i){
        uchar bit = (t&(1ull << 47))>>47;
        ba.add_bit(bit);
        t <<= 1;
    }
    for(int i = 0; i < 48; ++i){
        uchar bit = (l&(1ull << 47))>>47;
        ba.add_bit(bit);
        l <<= 1;
    }
    ASSERT_EQ(ba.length(), 96);
    ba.show_bit();
    uchar tmp = 0;
    for(int i = 0; i < ba.length(); ++i) {
        tmp <<= 1;
        tmp |= ba.get_bit(i);
        if ((i+1)%4==0) {
            printf("%x", tmp);
            tmp = 0;
        }
    }
    printf("\n");
    bit_array bb;
    bb.show_bit();
    bb.add_bits(ba);
    bb.show_bit();
}

TEST(BitArray, is_equal_0) {
    bit_array ba;
    for (int i = 0; i < 256; ++i) {
        ba.add_bit(0);
    }
    ASSERT_TRUE(ba.is_equal_0());
}

TEST(BitArray, rank) {
    bit_array ba;
    unlong t = 0xdeadcafedeadul;
    unlong l = 0xfacebeedfaceul;
    for(int i = 0; i < 48; ++i){
        uchar bit = (t&(1ull << 47))>>47;
        ba.add_bit(bit);
        t <<= 1;
    }
    for(int i = 0; i < 48; ++i){
        uchar bit = (l&(1ull << 47))>>47;
        ba.add_bit(bit);
        l <<= 1;
    } 
    ba.show_bit();

    ASSERT_EQ(ba.rank(95), 67);
    ASSERT_EQ(ba.rank(63), 44);
    ASSERT_EQ(ba.rank(67), 47);
}
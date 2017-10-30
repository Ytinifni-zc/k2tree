#include <bit_array.h>
#include <cstdio>
#include <cassert>

using namespace k2tree;

unlong bitrev(unlong n) {
    n = ((n>>1) & 0x5555555555555555) | ((n<<1) & 0xaaaaaaaaaaaaaaaa);
    n = ((n>>2) & 0x3333333333333333) | ((n<<2) & 0xcccccccccccccccc);
    n = ((n>>4) & 0x0f0f0f0f0f0f0f0f) | ((n<<4) & 0xf0f0f0f0f0f0f0f0);
    n = ((n>>8) & 0x00ff00ff00ff00ff) | ((n<<8) & 0xff00ff00ff00ff00);
    n = ((n>>16) & 0x0000ffff0000ffff) | ((n<<16) & 0xffff0000ffff0000);
    n = ((n>>32) & 0x00000000ffffffff) | ((n<<32) & 0xffffffff00000000);
    return n;
}

size_t bitcount(unlong n) {
    n = (n & 0x5555555555555555) + ((n >> 1) & 0x5555555555555555);
    n = (n & 0x3333333333333333) + ((n >> 2) & 0x3333333333333333);
    n = (n & 0x0f0f0f0f0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f0f0f0f0f);
    n = (n & 0x00ff00ff00ff00ff) + ((n >> 8) & 0x00ff00ff00ff00ff);
    n = (n & 0x0000ffff0000ffff) + ((n >> 16) & 0x0000ffff0000ffff);
    n = (n & 0x00000000ffffffff) + ((n >> 32) & 0x00000000ffffffff);
    return (size_t)n;
}

bit_array::bit_array(): length_(0) {
    bits_.resize(0);
}

bit_array::bit_array(bit_array* ba): length_(ba->length()) {
    size_t tmp = ba->bits().size();
    bits_.resize(tmp, 0x0l);
    for (int i = 0; i < tmp; ++i)
        bits_[i] = ba->bits()[i];
}

size_t bit_array::length() {
    return length_;
}

vector<unlong > bit_array::bits() {
    return bits_;
}

unlong bit_array::current_bits() {
    return *(bits_.end());
}

uchar bit_array::get_bit(size_t pos) {
    assert(pos <= SIZE*bits_.size());
    assert(pos <= length_);
    return (bits_[pos/SIZE] >> (pos%SIZE)) &1;

}

void bit_array::add_bit(uchar bit) {
    assert((bit==0 || bit==1));
    if (!(length_%SIZE)) 
        bits_.push_back(0x0);
    unlong tmp = bits_[bits_.size()-1];
    bits_[bits_.size()-1] = tmp | (((unlong)bit) << (length_%SIZE));
    ++length_;
}

void bit_array::add_bits(bit_array ba) {
    // TODO
    // 操作unlong或许速度更快
    for (int i = 0; i < ba.length(); ++i) {
        add_bit(ba.get_bit(i));
    }
    ba.clear();
}

void bit_array::set_bit(size_t pos, uchar bit) {
    assert((bit==0 || bit==1));
    assert(pos <= SIZE*bits_.size());
    assert(pos <= length_);
    if (bit) 
        bits_[pos/SIZE] |= (1ull << (pos%SIZE));
    else 
        bits_[pos/SIZE] &= ~(1ull << (pos%SIZE));
}

bool bit_array::is_equal_0() {
    unlong ret = 0x0;
    for (auto b : bits_) ret |= b;
    return ret == 0x0;
}

size_t bit_array::rank(size_t pos) {
    size_t rank = 0;
    for (int i = 0; i < pos/SIZE; ++i) {
        rank += bitcount(bits_[i]);
    }
    unlong tmp = bits_[pos/SIZE] & ((0xffffffffffffffffull >> (SIZE-1-pos%SIZE)));
    rank += bitcount(tmp);
    return rank;
}

void bit_array::clear() {
    bits_.clear();
    bits_.shrink_to_fit();
}

void bit_array::show_bit() {
    printf("bits: 0x");
    for (int i = 0; i < bits_.size(); ++i) {
        auto b = bitrev(bits_[i]);
        if (i == bits_.size()-1 && length_%SIZE) 
            b >>= (SIZE-(length_%SIZE));
        printf("%llx", b);
        
    }
    printf("\nlength: %d\n", length_);
}
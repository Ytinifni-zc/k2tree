#include <vector>
#include <cstdlib>
#include <gtest/gtest.h>

using std::vector;

const unsigned long long size = 512ull*1024*1024*8;
TEST(vb_test, vb_pushback) {
    vector<bool> vb;
    for (size_t i = 0; i < size; ++i)
        vb.push_back(true);
    
    ASSERT_EQ(vb.size(), size);
    for (size_t i = 0; i < size; ++i)
        vb[i] = false;
}

TEST(vb_test, vi_pushback) {
    vector<int> vb;
    for (size_t i = 0; i < size; ++i)
        vb.push_back(1);
    
    ASSERT_EQ(vb.size(), size);

    for (size_t i = 0; i < size; ++i)
        vb[i] = 2;
}

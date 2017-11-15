#include <gtest/gtest.h>
#include <sdsl/vectors.hpp>
#include <sdsl/coder_elias_gamma.hpp>
#include <sdsl/coder_comma.hpp>
#include <sdsl/coder_fibonacci.hpp>
#include <sdsl/bit_vectors.hpp>
#include <iostream>
#include <utils/bit_vector.h>

using namespace sdsl;
using namespace k2tree;
using std::cout;
using std::endl;

TEST(vector_test, int_vector) {
    int_vector<> v = {3,2,1,0,2,1,3,4,1,1,1,3,2,3};
    v[1]=0;
    util::bit_compress(v);
    cout << v << endl;
    ASSERT_EQ(size_in_bytes(v), 17);
}

/*
TEST(vector_test, int_vector2) {
    int_vector<> v(10*(1<<20));
    for (size_t i=0; i<10; ++i)
        for (size_t j=0; j < 1U<<20; ++j)
            v[i*(1<<20)+j] = j;
    // ASSERT_EQ(size_in_mega_bytes(v), (double)80);
    cout << size_in_mega_bytes(v) << endl;
    util::bit_compress(v);
    // ASSERT_EQ(size_in_mega_bytes(v), (double)25);
    cout << size_in_mega_bytes(v) << endl;
    enc_vector<coder::comma<>> ev(v);
    cout << size_in_mega_bytes(ev) << endl;
}

TEST(vector_test, fibonacci) {
    int_vector<> v(10*(1<<20), 0);
    v[0] = 1ULL<<63;
    //util::bit_compress(v);
    cout << size_in_mega_bytes(v) << endl;
    vlc_vector<coder::fibonacci> vv(v);
    cout << size_in_mega_bytes(vv) << endl;
    cout << "Percentage: " << size_in_mega_bytes(vv) / size_in_mega_bytes(v) * 100 << endl;
}

TEST(vector_test, bit_vector) {
    bit_vector b = {1,1,0,1,0,0,1};
    cout << b << endl;
    b = bit_vector(80*(1<<20), 0);
    for (size_t i=0; i < b.size(); i+=100)
        b[i] = 1;
    cout << size_in_mega_bytes(b) << endl;
}

TEST(vector_test, bit_rrrb) {
    bit_vector b = bit_vector(80*(1<<20), 0);
    for (size_t i=0; i < b.size(); i+=100)
        b[i] = 1;
    cout << size_in_mega_bytes(b) << endl;
    rrr_vector<63> rrrb(b);
    cout << size_in_mega_bytes(rrrb) << endl;
    sd_vector<> sdb(b);
    cout << size_in_mega_bytes(sdb) << endl;
}

TEST(vector_test, bit_write_json) {
    bit_vector b = bit_vector(80*(1<<20), 0);
    for (size_t i=0; i < b.size(); i+=100)
        b[i] = 1;
    sd_vector<> sdb(b);
    write_structure<JSON_FORMAT>(sdb, cout);
}
 */

TEST(vector_test, bit_rank) {
    bit_vector b = bit_vector(8000, 0);
    bit_vector c = bit_vector(8000, 0);
    for (size_t i=0; i < b.size(); i+=100) {
        b[i] = 1;
        c[i+1] = 1;
    }
    b |= c;
    rank_support_v<1> b_rank(&b);
    for (size_t i=0; i<=b.size(); i+= b.size()/4)
        cout << "(" << i << ", " << b_rank(i) << ") ";
    cout << endl;
}

TEST(vector_test, bit_rrr_rank) {
    bit_vector b = bit_vector(8000, 0);
    for (size_t i=0; i < b.size(); i+=100)
        b[i] = 1;
    sd_vector<> sdb(b);
    sd_vector<>::rank_1_type sdb_rank(&sdb);
    for (size_t i=0; i<=sdb.size(); i+= sdb.size()/4)
        cout << "(" << i << ", " << sdb_rank(i) << ") ";
    cout << endl;
    rrr_vector<> rrrb(b);
    rrr_vector<>::rank_1_type rrrb_rank(&rrrb);
    for (size_t i=0; i<=rrrb.size(); i+= rrrb.size()/4)
        cout << "(" << i << ", " << rrrb_rank(i) << ") ";
    cout << endl;
}

TEST(vector_test, bit_rank_2bits) {
    bit_vector b = {0,1,0,1};
    rank_support_v<1> b_r1(&b);
    rank_support_v<0> b_r0(&b);
    rank_support_v<10,2> b_r10(&b);
    rank_support_v<01,2> b_r01(&b);
    for (size_t i=0; i<=b.size(); ++i)
        cout << i << ": "<< b_r1(i) << " " << b_r0(i)
             << " " << b_r10(i) << " " << b_r01(i) << endl;
}

TEST(vector_test, bit_select) {
    bit_vector b = {0,1,0,1,1,1,0,0,0,1,1};
    size_t zeros = rank_support_v<0>(&b)(b.size());
    bit_vector::select_0_type b_sel(&b);

    for (size_t i=1; i <= zeros; ++i) {
        cout << b_sel(i) << " ";
    }
    cout << endl;
}

TEST(vector_test, bit_select_2bits) {
    bit_vector b = {0,1,0,1,1,1,0,0,0,1,1};
    size_t cnt10 = rank_support_v<10,2>(&b)(b.size());
    select_support_mcl<10,2> b_sel10(&b);

    for (size_t i=1; i <= cnt10; ++i)
        cout << b_sel10(i) << " ";
    cout << endl;
}

TEST(vector_test, bit_compressed_select) {
    sd_vector<> sd_b = bit_vector {1,0,1,1,1,0,1,1,0,0,1,0,0,1};
    size_t ones = sd_vector<>::rank_1_type(&sd_b)(sd_b.size());
    sd_vector<>::select_1_type sdb_sel(&sd_b);

    cout << sd_b << endl;

    for (size_t i=1; i <= ones; ++i)
        cout << sdb_sel(i) << " ";
    cout << endl;
}

TEST(vector_test, build_bv) {
    bit_vector b = {1,1,1,1,0,1,1};
    bit_vector bb = utils::int2bit_vector(123, 7);
    ASSERT_EQ(b, bb);

    int ret = utils::bit_vector2int(b);
    ASSERT_EQ(ret, 123);
}

TEST(vector_test, vector_bool) {
    vector<bool> bv = {true, true, true, true, false, true, true};
    vector<bool> bb = utils::int2vector_bool(123, 7);
    ASSERT_TRUE(bv == bb);

    int ret = utils::vector_bool2int(bv);
    ASSERT_EQ(ret, 123);
}

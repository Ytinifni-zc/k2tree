//
// Created by inFinity on 2017/12/1.
//

#include <gtest/gtest.h>
#include <k2tree_compressed.h>
#include <utils/time.h>
#include <utils/time.cc>

using namespace libk2tree;
using namespace std;

vector<size_t> get_rand(size_t length, int num) {
    random_device r;
    default_random_engine eg(r());
    uniform_int_distribution<int> uniform_dist(0, length-1);
    vector<size_t> ret(num, 0);
    for (auto r : ret) r = uniform_dist(eg);
    return ret;
}

shared_ptr<k2tree_compressed> read_twitter_partition(const int part_num, const int kL) {
    const string path = "/mnt/disk1/zhaocheng/dataset/twitter-2010/k2tree_partition/twitter"
                        +std::to_string(part_num)+".tree/kl"
                        +std::to_string(kL)+"/";
    const size_t node_num = 325409;

    shared_ptr<k2tree_compressed> kt =
            std::make_shared<k2tree_compressed>(2, 2, 1, kL, node_num, path, libk2tree::read_T, true);
    return kt;

}

void show(const k2tree_compressed &kt, int ws) {
    int length = (36>ws)?36:ws;
    for (int i = 0; i < length; ++i) {
        cout << kt.L()[i];
        if (0 == (i+1)%ws) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < length; ++i) {
        cout << kt.accessCompressL(i);
        if (0 == (i+1)%ws) cout << " ";
    }
    cout << endl;

    int err = 0;
    for (int i = 0; i < length; ++i) {
        if (kt.accessCompressL(i) != kt.L()[i])
            err++;
    }
    std::cout << err << std::endl;

}

int calculate_err(const k2tree_compressed &kt) {
    int err = 0;
    int length = 100; //kt.L().size()
    for (int i = 0; i < length; ++i) {
        if (kt.accessCompressL(i) != kt.L()[i])
            err++;
        if (0==((i+1)%100))
            cout << (i+1)/100 << endl;
    }
    utils::cost([&](){
        kt.accessCompressL(1);
    }, "us");
    utils::cost([&](){
        kt.accessCompressL(1000);
    }, "us");
    utils::cost([&](){
     for (int i = 0; i < length; ++i) {
        if (kt.accessCompressL(i) != kt.L()[i])
            err++;
        if (0==((i+1)%100))
            cout << (i+1)/100 << endl;
    }
    }, "us");
    return err;
}

TEST(ReadCompressedTree, test_csv) {
    const string path = "./k2tree/";
    const size_t node_num = 11;
    auto kL = 2;
    k2tree_compressed ktc(2, 2, 1, kL, node_num, path, libk2tree::read_T, true);

    ASSERT_EQ(ktc.accessCompressL(1), 1);
    ASSERT_EQ(ktc.accessCompressL(33), 1);
    ASSERT_EQ(ktc.accessCompressL(13), 0);

}

TEST(ReadCompressedTree, test_csv_kl4) {
    const string path = "./k2tree/kl4/";
    const size_t node_num = 11;
    auto kL = 4;
    k2tree_compressed ktc(2, 2, 1, kL, node_num, path, libk2tree::read_T, true);

    ASSERT_EQ(ktc.accessCompressL(1), 1);
    ASSERT_EQ(ktc.accessCompressL(33), 0);
    ASSERT_EQ(ktc.accessCompressL(6), 1);
    ASSERT_EQ(ktc.accessCompressL(7), 1);

}

TEST(ReadCompressedTwitter0, readT_kL4) {
    const int kL = 4;

    auto ktc = read_twitter_partition(0, kL);

    int err = calculate_err(*ktc);
    ASSERT_EQ(err, 0);
}

TEST(ReadCompressedTwitter0, readT_kL8) {
    const int kL = 8;

    auto ktc = read_twitter_partition(0, kL);

    int err = calculate_err(*ktc);
    ASSERT_EQ(err, 0);
}

TEST(ReadCompressedTwitter0, readT_kL16) {
    const int kL = 16;

    auto ktc = read_twitter_partition(0, kL);

    int err = calculate_err(*ktc);
    ASSERT_EQ(err, 0);
}

TEST(ReadCompressedTwitter8514, readT_kL4) {
    const int kL = 4;

    auto ktc = read_twitter_partition(8514, kL);

    int err = calculate_err(*ktc);
    ASSERT_EQ(err, 0);
}

TEST(ReadCompressedTwitter8514, readT_kL8) {
    const int kL = 8;

    auto ktc = read_twitter_partition(8514, kL);

    int err = calculate_err(*ktc);
    ASSERT_EQ(err, 0);
}

TEST(ReadCompressedTwitter8514, readT_kL16) {
    const int kL = 16;

    auto ktc = read_twitter_partition(8514, kL);

    int err = calculate_err(*ktc);
    ASSERT_EQ(err, 0);
}

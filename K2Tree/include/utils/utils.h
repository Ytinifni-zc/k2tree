//
// Created by zhaocheng on 17-11-21.
//

#ifndef K2TREE_UTILS_H
#define K2TREE_UTILS_H

#include <base.h>
#include <fstream>

namespace libk2tree {
    namespace utils {
        using std::ifstream;
        using std::ofstream;
        /**
         * Find the smallest prime greater or equal to n.
         * @param n
         * @return
         */
        size_t NearestPrime(size_t n);

        /**
         * Saves a value into an ofstream.
         * The type must be TriviallyCopyable
         */
        template <typename T>
        void SaveValue(ofstream *out, T val) {
            out->write(reinterpret_cast<char *>(&val), sizeof(T));
        }

        /**
         * Loads a value from an istream.
         * The type must be TriviallyCopyable
         */
        template <typename T>
        T LoadValue(ifstream *in) {
            T ret;
            in->read(reinterpret_cast<char *>(&ret), sizeof(T));
            return ret;
        }

        /**
         * Saves len values into an ofstream.
         * The type must be TriviallyCopyable
         */
        template <typename T>
        void SaveValue(ofstream *out, T *val, size_t length) {
            out->write(reinterpret_cast<char *>(val),
                         (std::streamsize) (length * sizeof(T)));
        }

        /**
         * Loads len values from an istream.
         * The type must be TriviallyCopyable
         */
        template <typename T>
        T *LoadValue(ifstream *in, size_t length) {
            T *ret = new T[length];
            in->read(reinterpret_cast<char *>(ret),
                       (std::streamsize) (length * sizeof(T)));
            return ret;
        }

        int strcmp(const uchar *w1, const uchar *w2, uint size);

    }
}

#endif //K2TREE_UTILS_H

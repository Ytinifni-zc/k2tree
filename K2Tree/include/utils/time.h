//
// Created by inFinity on 2017/11/8.
//

#ifndef K2TREE_TIME_H
#define K2TREE_TIME_H

#include <chrono>
#include <string>
#include <iostream>
#include <cassert>

namespace k2tree {
    namespace utils {
        template<typename L>
        void cost(L lambda, const std::string &unit="ms") {
            /**
             * Calculate runtime of a function
             * @param lambda lambda expression
             * @param unit computation unit. Must be ms or s.
             * @return
             */

            assert(unit=="ms" || unit=="s");

            auto start = std::chrono::system_clock::now();
            lambda();
            auto end = std::chrono::system_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            auto den = std::chrono::milliseconds::period::den;
            if (unit == "s") den = std::chrono::microseconds::period::den;
            std::cout << "[" << double(duration.count())
                                *std::chrono::microseconds::period::num / den
                      << unit << "]" << std::endl;
        }
    }
}

#endif //K2TREE_TIME_H

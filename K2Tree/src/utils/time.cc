//
// Created by inFinity on 2017/11/13.
//

#include <utils/time.h>
#include <chrono>
#include <iostream>
#include <cassert>

template<typename L>
void libk2tree::utils::cost(L lambda, const std::string &unit) {

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

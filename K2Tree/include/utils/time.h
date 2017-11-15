//
// Created by inFinity on 2017/11/8.
//

#ifndef K2TREE_UTILS_TIME_H
#define K2TREE_UTILS_TIME_H

#include <string>

namespace k2tree {
    namespace utils {
        /**
         * Calculate runtime of a function
         * @tparam L lambda expression
         * @param lambda lambda expression
         * @param unit computation unit. Must be ms or s.
         */
        template<typename L>
        void cost(L lambda, const std::string &unit="ms");
    }
}

#endif //K2TREE_UTILS_TIME_H

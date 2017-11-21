//
// Created by zhaocheng on 17-11-21.
//

#include <utils/utils.h>

size_t libk2tree::utils::NearestPrime(size_t n){
    /* the prime number being sought */
    size_t pos;
    size_t i;

    for (pos = n; ; pos++) {
        // checks if those values from 2 to $\sqrt{pos}$ can be factors of $pos$
        for (i = 2; i <= pos/i + 1 && pos % i != 0; i++) ;
        // No factors in that range, therefore a prime number was found
        if (pos % i != 0)
            break;
    }
    return pos;
}

int ::libk2tree::utils::strcmp(const libk2tree::uchar *w1, const libk2tree::uchar *w2, libk2tree::uint size) {
    uint i = 0;
    while (i < size - 1 && *w1 == *w2) {
        ++w1;
        ++w2;
        ++i;
    }
    return (int) *w1 - (int) *w2;
}

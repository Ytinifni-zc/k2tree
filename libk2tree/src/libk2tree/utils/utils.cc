/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * ----------------------------------------------------------------------------
 *
 * Refer to utils.h for more details.
 *
 */

#include <utils/utils.h>

namespace libk2tree {
namespace utils {


int SquaringPow(int base, int exp) {
  // Iterative aproach that increase pow
  // for every bit on true in exp.
  int pow;
  for (pow = 1; exp; base *= base, exp >>= 1)
    if (exp & 1)
      pow *= base;
  return pow;
}

/**
 * Find the smallest prime greater or equal to n
 */
size_t NearestPrime(size_t n) {
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

int strcmp(const uchar *w1, const uchar *w2, uint size) {
  uint i = 0;
  while (i < size - 1 && *w1 == *w2) {
    ++w1;
    ++w2;
    ++i;
  }
  return (int) *w1 - (int) *w2;
}

}  // namespace utils
}  // namespace libk2tree

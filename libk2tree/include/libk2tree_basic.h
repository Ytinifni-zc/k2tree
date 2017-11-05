/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * ----------------------------------------------------------------------------
 */

#ifndef INCLUDE_LIBK2TREE_BASIC_H_
#define INCLUDE_LIBK2TREE_BASIC_H_
#include <cstdlib>
namespace libk2tree {
typedef unsigned int uint;
typedef unsigned char uchar;
/** Size for number of objects */
//typedef size_t cnt_size;
typedef size_t cnt_size;
/** Number of bits in a byte */
const uint kByteBits = 8;
/** Number of bits in an unsigned char */
const uint kUcharBits = kByteBits*sizeof(uchar);
}  // namespace libk2tree
#endif  // INCLUDE_LIBK2TREE_BASIC_H_

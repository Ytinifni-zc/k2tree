//
// Created by zhaocheng on 17-11-20.
//

#ifndef K2TREE_FILE_H
#define K2TREE_FILE_H

#include <sys/stat.h>

namespace libk2tree {
    namespace utils {
        /**
         * Given path of file, return size of this file.
         * @param path Path of file.
         * @return Size of this file.
         */
        long int get_file_size(const char *path);
    }
}


#endif //K2TREE_FILE_H

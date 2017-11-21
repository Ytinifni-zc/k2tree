//
// Created by zhaocheng on 17-11-20.
//

#include <utils/file.h>

long int ::libk2tree::utils::get_file_size(const char *path) {
    auto filesize = static_cast<long int>(-1);
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
        return filesize;
    else
        filesize = statbuff.st_size;
    return filesize;
}

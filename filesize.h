
#ifndef PROJECT_FILESIZE_H
#define PROJECT_FILESIZE_H

#include <string>
#include <iostream>

#define KB 1000
#define MB 1000000
#define GB 1000000000
#define TB 1000000000000
#define PB 1000000000000000

void show_filesize(std::uintmax_t size) {
    if (size >= KB && size < MB) std::cout <<  size / KB  << " KB";
    if (size >= MB && size < GB) std::cout <<  size / MB  << " MB";
    if (size >= GB && size < TB) std::cout <<  size / GB  << " GB";
    if (size >= TB && size < PB) std::cout <<  size / TB  << " TB";
    if (size >= PB) std::cout <<  size / PB  << " PB";
    std::cout <<  size  << " Bytes";
}

#endif //PROJECT_FILESIZE_H

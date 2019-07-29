//
// Created by nires on 26-May-19.
//

#include "Measurements.h"

//#include <iostream>

Measurements::Measurements(const Measurements &m2) {
    inCacheTime = m2.inCacheTime;
    noCacheTime = m2.noCacheTime;
    accessTimes.clear();
    for(const auto& i : m2.accessTimes){
        MemoryAccess newAccess = {i.timeOfMeasure, i.clockCycles, i.speculatedCache};
        accessTimes.push_back(newAccess);
    }
}

Cache Measurements::SpeculatedCache(unsigned int clockCycles) {
    int avg = (this->inCacheTime + this->noCacheTime)/2;
    if (clockCycles > avg){
        return Memory;
    }
    return L3;
}

void Measurements::AddMeasurement(std::time_t measureTime, unsigned int clockCycles) {
    MemoryAccess newAccess = {measureTime, clockCycles, SpeculatedCache(clockCycles)};
    accessTimes.push_back(newAccess);
}

void Measurements::UpdateSpeculations() {
    for (auto& i : accessTimes){
        i.speculatedCache = SpeculatedCache(i.clockCycles);
    }
}
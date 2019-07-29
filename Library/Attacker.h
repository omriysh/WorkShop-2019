//
// Created by nires on 23-May-19.
//

#ifndef WORKSHOP_ATTACKER_H
#define WORKSHOP_ATTACKER_H

#include "Measurements.h"
#include "Victim.h"

class Attacker {
private:
    Victim victim;
    char *targetPointer;
    char *targetData;
    int targetDataLen;
    unsigned int inCacheTime;
    unsigned int noCacheTime;
    bool attacking;
    Measurements measurements;
    int interval;
    int maxIterations;

    int MeasureTime(volatile char *ch);

public:
    Attacker(std::string path);
    Attacker(std::string path, char *target, int len);
    Attacker(std::string path, char *target, int len, int intervalTime);
    Attacker(std::string path, char *target, int len, int intervalTime, int iterations);

    void SetTarget(char *data, int len) { targetData = data; targetDataLen = len; }
    void SetInCacheTime(unsigned int time) { inCacheTime = time; measurements.SetInCacheTime(time);}
    void SetNoCacheTime(unsigned int time) { noCacheTime = time; measurements.SetNoCacheTime(time);}
    void SetInterval(int time) { interval = time; }
    void SetMaxIterations(int iterations) { maxIterations = iterations; }

    Measurements GetMeasurements() { Measurements newInstance = measurements; return newInstance; }

    virtual void Configure() =0;
    virtual void Attack() =0;
};
#endif //WORKSHOP_ATTACKER_H

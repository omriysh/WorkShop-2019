//
// The base class of an attacker.
// An attacker has a target pointer which will be attacked. It can be set
// manually by the user, or automatically by the attacker using the Victim
// class, if the user chooses to provide a path and target data.
// Attack and Configure here are virtual, and should be implemented by the child.
// Basic ctors, dtor, getters and setters are implemented here, as well
// as the MeasureTime utility.
//

#ifndef WORKSHOP_ATTACKER_H
#define WORKSHOP_ATTACKER_H

#include "Measurements.h"
#include "Victim.h"

class Attacker {
protected:
    Victim *victim;             // victim instance (holding data and finding the target)
    char *targetPointer;        // the pointer to the actual target
    char *targetData;           // holds the data to look for within the file
    int targetDataLen;          // len of targetData
    unsigned int inCacheTime;   // avg time to access when in L3
    unsigned int noCacheTime;   // avg time to access when in memory
    Measurements measurements;  // measurements instance holding records from previous attack
    int interval;               // the time to wait between samples (in Attack)
    int maxIterations;          // the amount of iterations (in Attack)

    // Measures the time it takes to access ch in clock cycles,
    // as accurately as possible.
    // THIS FUNCTION IS ALWAYS INLINED.
    unsigned int MeasureTime(volatile char *ch);

public:
    // ~~~~~~~~~~~~~~~~~~~~~~~ ctors ~~~~~~~~~~~~~~~~~~~~~~~
    // basic, empty ctor - to use when targetPointer is known and no
    // victim is needed.
    Attacker();
    // basic ctor with input to victim (target here is target data).
    Attacker(std::string path, char *target, int len);
    // basic ctor with input to victim and intervalTime (target here is target data).
    Attacker(std::string path, char *target, int len, int intervalTime);
    // basic ctor with input to victim, intervalTime and iterations (target here is target data).
    Attacker(std::string path, char *target, int len, int intervalTime, int iterations);

    // ~~~~~~~~~~~~~~~~~~~~~~~ dtors ~~~~~~~~~~~~~~~~~~~~~~~
    // basic dtor.
    virtual ~Attacker();

    // ~~~~~~~~~~~~~~~~~~~~~~~ getters & setters ~~~~~~~~~~~~~~~~~~~~~~~ (self explanatory)
    void SetTarget(char *target) { targetPointer = target; }
    void SetInCacheTime(unsigned int time) { inCacheTime = time; measurements.SetInCacheTime(time);}
    void SetNoCacheTime(unsigned int time) { noCacheTime = time; measurements.SetNoCacheTime(time);}
    void SetInterval(int time) { interval = time; }
    void SetMaxIterations(int iterations) { maxIterations = iterations; }
    Measurements GetMeasurements() { Measurements newInstance = measurements; return newInstance; }

    // ~~~~~~~~~~~~~~~~~~~~~~~ attacking functions ~~~~~~~~~~~~~~~~~~~~~~~
    // This function should be implemented by a child of Attacker. It's purpose is
    // to provide automatic setup for the attack, such as setting in/no-CacheTime, etc.
    virtual void Configure() =0;
    // This function should be implemented by a child of Attacker. It is the main
    // attacking function, and it will attack targetPointer and update the measures
    // in measurements. The specific details change from attack to attack.
    virtual void Attack() =0;
};
#endif //WORKSHOP_ATTACKER_H

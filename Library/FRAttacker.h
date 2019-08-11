//
// FRAttacker - Flush Reload Attacker.
// This class implements the Attacker class, creating a capable flush reload
// attacker. The attack works by flushing the target out of cache memory
// (by using clflush), waiting and measuring access time. The results can then
// be inspected by the user by calling GetMeasurements and observing the vector
// of MemoryAccesses.
//

#ifndef WORKSHOP_FRATTACKER_H
#define WORKSHOP_FRATTACKER_H

#include "Attacker.h"

using namespace std;

class FRAttacker : public Attacker {
private:
    // private utility that flushes toFlush with clflush. will be always inlined.
    void Flush(void* toFlush);

public:
    // ~~~~~~~~~~~~~~~~~~~~~~~ ctors ~~~~~~~~~~~~~~~~~~~~~~~ (same as Attacker)
    FRAttacker();
    FRAttacker(string path, char* target, int len);
    FRAttacker(string path, char* target, int len, int intervalTime);
    FRAttacker(string path, char* target, int len, int intervalTime, int iteration);

    // ~~~~~~~~~~~~~~~~~~~~~~~ attacking functions ~~~~~~~~~~~~~~~~~~~~~~~
    // Here, configure finds out inCacheTime and noCacheTime - the average time it
    // takes to access the cache vs the memory. It does so by running a pre-determined
    // number of iterations and calculating an average of how long it takes to read the
    // target when in cache, and an average of how long it takes to read the target when
    // flushed. Note: this means target must be defined before calling Configure!
    void Configure();
    // Here, attack performs the flush-reload attack described above (in the beginning
    // of this file). It runs for maxIterations, each iteration works as follows:
    //      - flush target from cache
    //      - wait interval ns
    //      - measure access time to target and record measurement
    // After this function does it's thing, GetMeasurements will return the latest
    // measurements updated with speculations.
    void Attack();
};


#endif //WORKSHOP_FRATTACKER_H

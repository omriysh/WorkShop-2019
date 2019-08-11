//
// PPAttacker - Prime and Probe Attacker.
// This isn't prime and probe and the usual sense, it's very simplified.
// This works again with the model of attacking a known pointer, and we
// assume the attacker has reading access to the pointer but no flushing
// possibilities. Thus, the attack will prime L3 to "flush" the target out,
// and then measure time reading it.
//

#ifndef WORKSHOP_PPATTACKER_H
#define WORKSHOP_PPATTACKER_H

#include "Attacker.h"

using namespace std;

class PPAttacker : public Attacker {
private:
    int L3Size;         // storing the size of L3, calculated by Configure
    int L3LineSize;     // storing the line size of L3, calculated bt Configure

public:
    // ~~~~~~~~~~~~~~~~~~~~~~~ ctors ~~~~~~~~~~~~~~~~~~~~~~~ (same as Attacker)
    PPAttacker();
    PPAttacker(string path, char* target, int len);
    PPAttacker(string path, char* target, int len, int intervalTime);
    PPAttacker(string path, char* target, int len, int intervalTime, int iteration);

    // ~~~~~~~~~~~~~~~~~~~~~~~ attacking functions ~~~~~~~~~~~~~~~~~~~~~~~
    // Configure finds out inCacheTime and noCacheTime - the average time it
    // takes to access the cache vs the memory - and also some properties of L3, it's
    // size and line size. The cache times are found by running a pre-determined
    // number of iterations and calculating an average of how long it takes to read a
    // local variable when in cache, and an average of how long it takes to read the
    // same variable when priming L3. The properties of L3 are found by running a command
    // and works only on Linux.
    void Configure();
    // Attack performs the prime and probe attack described above (in the beginning
    // of this file). It runs for maxIterations, each iteration works as follows:
    //      - prime L3
    //      - wait interval ns
    //      - measure access time to target and record measurement
    // After this function does it's thing, GetMeasurements will return the latest
    // measurements updated with speculations.
    void Attack();
};


#endif //WORKSHOP_PPATTACKER_H

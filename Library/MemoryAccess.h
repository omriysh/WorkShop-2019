//
// Created by nires on 26-May-19.
//

#ifndef WORKSHOP_MEMORYACCESS_H
#define WORKSHOP_MEMORYACCESS_H

enum Cache {
    noSpeculation,
    L1,
    L2,
    L3,
    Memory
};

struct MemoryAccess {
    std::time_t timeOfMeasure;
    unsigned int clockCycles;
    Cache speculatedCache;
};
#endif //WORKSHOP_MEMORYACCESS_H
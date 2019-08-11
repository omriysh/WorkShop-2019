#ifndef WORKSHOP_MEMORYACCESS_H
#define WORKSHOP_MEMORYACCESS_H

// enum used for cache talk ;)
enum Cache {
    noSpeculation,
    L1,
    L2,
    L3,
    Memory
};

// the struct that holds a single memory access
struct MemoryAccess {
    std::time_t timeOfMeasure;  // time of measurement, 'cause why not
    unsigned int clockCycles;   // clock cycles - the actual measurement
    Cache speculatedCache;      // the speculation of this measurement
};
#endif //WORKSHOP_MEMORYACCESS_H
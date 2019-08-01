//
// Created by User on 18/5/2019.
//

#ifndef WORKSHOP_PPATTACKER_H
#define WORKSHOP_PPATTACKER_H

#include "Attacker.h"

using namespace std;

class PPAttacker : public Attacker {
private:
    int L3Size;
    int L3LineSize;
    int L3Assoc;

    char* buffer;
    int index;

    void BombL3();

public:
    PPAttacker();
    PPAttacker(int intervalTime);
    PPAttacker(int intervalTime, char* target);
    ~PPAttacker();

    void Configure();
    void Attack();
};


#endif //WORKSHOP_PPATTACKER_H

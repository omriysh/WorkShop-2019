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

public:
    PPAttacker();
    PPAttacker(int intervalTime);

    void Configure();
    void Attack();
};


#endif //WORKSHOP_PPATTACKER_H

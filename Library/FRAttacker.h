//
// Created by User on 18/5/2019.
//

#ifndef WORKSHOP_FRATTACKER_H
#define WORKSHOP_FRATTACKER_H

#include "Attacker.h"

using namespace std;

class FRAttacker : Attacker {

public:
    FRAttacker(string path);
    FRAttacker(string path, char* target, int len);
    FRAttacker(string path, char* target, int len, int intervalTime);
    FRAttacker(string path, char* target, int len, int intervalTime, int iteration);

    void Configure();
    void Attack();
};


#endif //WORKSHOP_FRATTACKER_H

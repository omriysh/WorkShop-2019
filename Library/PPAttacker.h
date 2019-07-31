//
// Created by User on 18/5/2019.
//

#ifndef WORKSHOP_PPATTACKER_H
#define WORKSHOP_PPATTACKER_H

#include "Attacker.h"

using namespace std;

class PPAttacker : public Attacker {
public:
    PPAttacker(string path);
    PPAttacker(string path, char* target, int len);
    PPRAttacker(string path, char* target, int len, int intervalTime);
    PPAttacker(string path, char* target, int len, int intervalTime, int iteration);

    void Configure();
    void Attack();
};


#endif //WORKSHOP_PPATTACKER_H

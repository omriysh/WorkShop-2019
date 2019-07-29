//
// Created by User on 18/5/2019.
//

#include "FRAttacker.h"

using namespace std;


FRAttacker::FRAttacker(string path) :
    Attacker(path);

FRAttacker::FRAttacker(string path, char* target, int len) :
    Attacker(path, target, len);

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime) :
    Attacker(path, target, len, intervalTime);

FRAttacker::FRAttacker(string path, char* target, int len, int intervalTime, int iteration) :
    Attacker(path, target, len, intervalTime, iteration);

void FRAttacker::Attack() {
    // declaring variables

    // logic
    // create a new measurements class
    measurements = Measurements();



    // wrap up
}
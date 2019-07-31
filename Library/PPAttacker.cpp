//
// Created by User on 18/5/2019.
//

#include "PPAttacker.h"

PPAttacker::PPAttacker(string path) :
        Attacker(path) {}

PPAttacker::PPAttacker(string path, char* target, int len) :
        Attacker(path, target, len) {}

PPAttacker::PPAttacker(string path, char* target, int len, int intervalTime) :
        Attacker(path, target, len, intervalTime) {}

PPAttacker::PPAttacker(string path, char* target, int len, int intervalTime, int iteration) :
        Attacker(path, target, len, intervalTime, iteration) {}


void PPAttacker::Attack() {
    // declaring variables


    // logic

}

void PPAttacker::Configure() {
    // declaring variables


    //logic

}
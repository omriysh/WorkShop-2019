//
// Created by nires on 29-Jul-19.
//

#include "FRAttacker.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv){
    // set up arguments for the attack
    int iterations = 100;
    int interval = 1;
    if(argc < 3 || argc > 5){
        cout << "WRONG USAGE: test path target [interval] [iterations]";
        return 1;
    }
    if(argc >= 4){
        interval = stoi(argv[3])
    }
    if (argc == 5){
        iterations = stoi(argv[4]);
    }
    FRAttacker attack = FRAttacker(argv[1], argv[2], strlen(argv[1]), interval, iterations);
    attack.Configure();
    attack.Attack();
}
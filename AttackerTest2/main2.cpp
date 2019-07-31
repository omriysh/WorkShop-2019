//
// Created by User on 31/7/2019.
//

#include <string.h>
#include <iostream>
#include "../Library/Measurements.h"
#include "../Library/FRAttacker.h"
#include "../Library/MemoryAccess.h"

using namespace std;

int main(int argc, char** argv)
{
    // declaring variables
    string path = "/mnt/c/Users/User/Documents/Arazim/Workshop/WorkShop-2019/testing/test2victim";
    char target[] = {'\xc7', '\x45', '\xfc', '\x06', '\x00'};
    Measurements measurements;

    //logic
    cout << "We are up and running! :)" << endl;

    FRAttacker attacker = FRAttacker(path, target, 5, 1000, 1);
    attacker.Configure();

    cout << "Attacker configured" << endl;

    while (true)
    {
        attacker.Attack();
        measurements = attacker.GetMeasurements();
        for (auto& access : measurements.GetAccessVector())
        {
            if (access.speculatedCache == Cache::L3)
            {
                cout << "Recorded access at time " << access.timeOfMeasure << endl;
            }
        }
    }

    //wrap up and return
    return 0;
}
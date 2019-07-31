//
// Created by User on 31/7/2019.
//

#include <string.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "../Library/Measurements.h"
#include "../Library/PPAttacker.h"
#include "../Library/MemoryAccess.h"

using namespace std;

int main(int argc, char** argv)
{
    // declaring variables
    Measurements measurements;
    int secsBetweenAttacks = 10;

    //logic
    cout << "We are up and running! :)" << endl;

    PPAttacker attacker = PPAttacker(1000);
    attacker.Configure();

    cout << "Attacker configured" << endl;
    cout << "Attacking once every " << secsBetweenAttacks << " seconds" << endl;

    while (true)
    {
        cout << "Attacking!" << endl;
        attacker.Attack();
        measurements = attacker.GetMeasurements();
        for (auto& access : measurements.GetAccessVector())
        {
            if (access.speculatedCache == Cache::L3)
                cout << "1";
            else
                cout << "0";
            cout << " " << endl;
        }
        usleep(secsBetweenAttacks * 1000000);
    }

    //wrap up and return
    return 0;
}
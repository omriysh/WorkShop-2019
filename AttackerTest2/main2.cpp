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
    const int secsBetweenAttacks = 2;
    const int charsInLine = 80;
    int inCounter;
    int noCounter;

    //logic
    cout << "We are up and running! :)" << endl;

    PPAttacker attacker = PPAttacker(10000);
    attacker.Configure();

    cout << "Attacker configured" << endl;
    cout << "Attacking once every " << secsBetweenAttacks << " seconds" << endl;

    while (true)
    {
        cout << "Attacking!" << endl;
        attacker.Attack();
        measurements = attacker.GetMeasurements();
        int counter = 0;
        inCounter = noCounter = 0;
        for (auto& access : measurements.GetAccessVector())
        {
            if (access.speculatedCache == Cache::L3) {
                //cout << "1";
                inCounter++;
            }
            else {
                //cout << "0";
                noCounter++;
            }
            /*cout << " ";
            if (counter++ % charsInLine == 0)
                cout << endl;*/
        }
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ in: " << inCounter << " out: " << noCounter << endl;
        usleep(secsBetweenAttacks * 1000000);
    }

    //wrap up and return
    return 0;
}

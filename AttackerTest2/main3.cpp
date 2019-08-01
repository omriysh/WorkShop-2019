//
// Created by User on 1/8/2019.
//

#include <string.h>
#include <iostream>
#include "../Library/Measurements.h"
#include "../Library/PPAttacker.h"
#include "../Library/MemoryAccess.h"

using namespace std;

int main(int argc, char** argv)
{
    // declaring variables
    string path = "/mnt/c/Users/User/Documents/Arazim/Workshop/WorkShop-2019/testing/test2victim";
    char target[] = {'\xc7', '\x45', '\xfc', '\x06', '\x00'};
    char* targetPointer;
    Measurements measurements;

    //logic
    cout << "We are up and running! :)" << endl;

    Victim victor = Victim(path);
    victor.LoadFile();
    targetPointer = victor.FindInFile(target, 5);

    cout << "Victim configured" << endl;

    PPAttacker attacker = PPAttacker(1000, targetPointer);
    attacker.Configure();

    cout << "Attacker configured" << endl;

    while (true)
    {
        attacker.Attack();
        measurements = attacker.GetMeasurements();
        int counter = 0;
        for (auto& access : measurements.GetAccessVector())
        {
            if (access.speculatedCache == Cache::L3)
            {
                counter++;
                //cout << "Recorded access at time " << access.timeOfMeasure << endl;
            }
        }
        if (counter > 0)
        {
            cout << counter << " Accesses recorded at time " << time(NULL) << endl;
        }
    }

    //wrap up and return
    return 0;
}
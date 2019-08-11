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

PPAttacker::PPAttacker() :
        Attacker() {}

PPAttacker::PPAttacker(string path, char* target, int len) :
        Attacker(path, target, len) {}

PPAttacker::PPAttacker(string path, char* target, int len, int intervalTime) :
        Attacker(path, target, len, intervalTime) {}

PPAttacker::PPAttacker(string path, char* target, int len, int intervalTime, int iteration) :
        Attacker(path, target, len, intervalTime, iteration) {}


void PPAttacker::Attack() {
    // declaring variables
    unsigned int measured;
    char buffer[L3Size];

    // logic
    // create a new measurements class
    measurements = Measurements();
    measurements.SetInCacheTime(inCacheTime);
    measurements.SetNoCacheTime(noCacheTime);

    // check dependencies
    if (inCacheTime == 0 || noCacheTime == 0)
        throw logic_error("inCacheTime or noCacheTime not set. please set them manually or run Configure()");
    if (L3Size == 0 || L3LineSize == 0)
        throw logic_error("please run Congifure()");
    if (interval == 0)
        throw logic_error("interval not set. please set manually");
    if (targetPointer == nullptr)
        throw logic_error("target not set. please set manually");

    // main attacking loop
    for (int i = 0; i < maxIterations; i++) {
        // bomb L3
        for (int i = 0; i < L3Size; i += L3LineSize) {
            buffer[i]++;
        }
        // wait
        usleep(interval);
        // measure
        measured = MeasureTime(targetPointer);
        //if (measured < 100) cout << measured << endl;
        measurements.AddMeasurement(time(NULL), measured);
    }
    measurements.UpdateSpeculations();
}


/*
void PPAttacker::Attack() {
    // declaring variables
    char buffer[L3Size];
    unsigned int measured;
    const int wordSize = 1;

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
*/

void PPAttacker::Configure() {
    int i;
    unsigned int cyclesSum = 0;
    int numOfIterations = 1000;
    char* testingPointer;

    // find out L3 size and line size by using getconf
    L3Size = stoi(GetAfterSpaces(Exec("getconf -a | grep LEVEL3_CACHE_SIZE")));
    L3LineSize = stoi(GetAfterSpaces(Exec("getconf -a | grep LEVEL3_CACHE_LINESIZE")));
    L3Assoc = stoi(GetAfterSpaces(Exec("getconf -a | grep LEVEL3_CACHE_ASSOC")));

    // allocate buffer
    char buffer[L3Size];

    // try and find out in cache and not in cache times (without flushing)
    // set up pointer
    char tester[L3LineSize*4];
    testingPointer = tester + L3LineSize*2;
    // measure
    for (i = 0; i < numOfIterations; i++) {
        for (int j = 0; j < L3Size; j += L3LineSize) {
            buffer[j]++;
        }
        cyclesSum += MeasureTime(testingPointer);
    }
    SetNoCacheTime(cyclesSum / numOfIterations);
    cyclesSum = 0;
    MeasureTime(testingPointer); /* makes sure target pointer has been recently read */
    for (i = 0; i < numOfIterations; i++){
        cyclesSum += MeasureTime(testingPointer);
    }
    SetInCacheTime(cyclesSum / numOfIterations);

    //cout << "in time: " << inCacheTime << endl;
    //cout << "no time: " << noCacheTime << endl;

    //cout << "---------" << endl << "Configuration:" << endl;
    //cout << "in time: " << inCacheTime << endl;
    //cout << "no time: " << noCacheTime << endl;
    //cout << "L3 size: " << L3Size      << endl;
    //cout << "L3 line: " << L3LineSize  << endl;
    //cout << "L3 asso: " << L3Assoc     << endl;
    //cout << "---------" << endl;
}
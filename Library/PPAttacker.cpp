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


// ~~~~~~~ helper functions ~~~~~~~

// this function executes a console command and returns the output (stdout only)
string exec(const char* cmd) {
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


// ~~~~~~~ PPAttacker functions ~~~~~~~

PPAttacker::PPAttacker(string path) :
        Attacker(move(path)) {}

PPAttacker::PPAttacker(string path, char* target, int len) :
        Attacker(move(path), target, len) {}

PPAttacker::PPAttacker(string path, char* target, int len, int intervalTime) :
        Attacker(move(path), target, len, intervalTime) {}

PPAttacker::PPAttacker(string path, char* target, int len, int intervalTime, int iteration) :
        Attacker(move(path), target, len, intervalTime, iteration) {}


void PPAttacker::Attack() {
    // declaring variables


    // logic

}

void PPAttacker::Configure() {
    // declaring variables


    //logic

}
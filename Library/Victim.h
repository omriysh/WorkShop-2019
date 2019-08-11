//
// Created by User on 18/5/2019.
//

#ifndef WORKSHOP_VICTIM_H
#define WORKSHOP_VICTIM_H

#include <string>

using namespace std;

class Victim {
private:
    // fields
    string path;
    char* fileData;
    int fileLen;

public:
    // basic ctor
    Victim(string Path);
    // basic dtor
    ~Victim();

    // This function maps the file to memory, loading it's contents into
    // fileData (initializing also fileLen) as read only and map shared.
    void LoadFile();
    // This function searches the file for the target data given by the pair
    // data and len, and returns the address of it's first appearance.
    char* FindInFile(const char* data, int len);
};


#endif //WORKSHOP_VICTIM_H

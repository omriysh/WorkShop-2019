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
    // functions
    Victim(string Path);
    ~Victim();
    void LoadFile();
    char* FindInFile(char* data, int len);

};


#endif //WORKSHOP_VICTIM_H

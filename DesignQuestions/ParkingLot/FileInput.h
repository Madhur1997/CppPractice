#include "InputInterface.h"
#include<string>
#include<iostream>
#include<fstream>
#include "ParkingLot.h"

using namespace std;

class FileInput : public InputInterface {
    string fileName_;
public:
    FileInput(string fileName) : fileName_(fileName) {

    }
    void start() {
        ParkingLot* parkingLot;
        ifstream f1(fileName_);
        string command;
        while(getline(f1, command)) {
            
        }
    }
};
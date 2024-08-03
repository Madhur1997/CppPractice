#include "InputInterface.h"
#include <iostream>

using namespace std;

class CLIInput : public InputInterface {
public:
    void start() {
        while(true) {
            string command;
            getline(cin, command);
            

        }
    }
};
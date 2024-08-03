#include <iostream>
#include "Enums.h"
#include "Car.h"

using namespace std;

class Slot {
    int slotNumber_;
    SlotState state_;
    Car* car_;

public:
    Slot(int slotNumber) : slotNumber_(slotNumber), state_(SlotState::Free), car_(nullptr) {}
    bool isColor(string color);
    bool isFree();
    void park(Car* car);
    void leave();
    

};
#include "Slot.h"

using namespace std;

bool Slot::isColor(string color) {
    if(state_ == SlotState::Free) {
        return false;
    }
    return car_->color() == color;
}

void Slot::park(Car* car) {
    if(state_ != SlotState::Free) {
        throw "Slot is already occupied";
    }

    state_ = SlotState::Occupied;
    car_ = car;
}

void Slot::leave() {
    state_ = SlotState::Free;
    car_ = nullptr;
}

bool Slot::isFree() {
    return state_ == SlotState::Free;
}
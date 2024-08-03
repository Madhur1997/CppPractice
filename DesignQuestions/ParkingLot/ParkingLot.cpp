#include "ParkingLot.h"
#include <vector>

using namespace std;

ParkingLot::ParkingLot(int capacity) : capacity_(capacity) {
    parkingTicketId_ = 0;
    for (int i = 0; i < capacity; i++) {
        slots_.push_back(new Slot(i));
    }
}

int ParkingLot::getNextSlot() {
    for (int i = 0; i < capacity_; i++) {
        if (slots_[i]->isFree()) {
            return i;
        }
    }
    return -1;
}

ParkingTicket ParkingLot::createParkingTicket(int slotNumber) {
    return ParkingTicket(slotNumber, parkingTicketId_++);
}


ParkingTicket ParkingLot::park(string registrationNumber, string color) {
    int slotNumber = getNextSlot();
    if (slotNumber == -1) {
        throw runtime_error("Parking lot is full");
    }
    slots_[slotNumber]->park(new Car(registrationNumber, color));
    
    return createParkingTicket(slotNumber);
}

void ParkingLot::leave(ParkingTicket parkingTicket, string registrationNumber) {
    int slotNumber = parkingTicket.slotNumber();
    if()
    slots_[slotNumber]->leave();
}
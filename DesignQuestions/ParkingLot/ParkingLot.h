#include "Slot.h"
#include "ParkingTicket.h"
#include<vector>

using namespace std;

/* 
FR: 
1. Input through a file or a CLI
2. Input will have commands to park, leave, create parking lot of given size, queries like:
    a. Get all cars by a given color
    b. Get all slots by a given color
    c. Get slot by reg number.
3. When car enters, next available parking slot is assigned and a ticket is generated.
*/

class ParkingLot {
    vector<Slot*> slots_;
    int capacity_;
    int parkingTicketId_;
    int getNextSlot();
    ParkingTicket createParkingTicket(int slotNumber);

public:
    ParkingLot(int capacity);
    ParkingTicket park(string registrationNumber, string color);
    void leave(ParkingTicket parkingTicket, string registrationNumber);
    vector<string> getRegistrationNumbersByColor(string color);
    vector<int> getSlotsByColor(string color);
    vector<int> getSlotByRegistrationNumber(string registrationNumber);
};
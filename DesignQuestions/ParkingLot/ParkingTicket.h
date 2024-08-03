#include<string>
#include<chrono>

using namespace std;

class ParkingTicket {
    int slotNumber_;
    int parkingTicketId_;
    string time_;
public:
    ParkingTicket(int slotNumber, int parkingTicketId) : slotNumber_(slotNumber), parkingTicketId_(parkingTicketId) {
        time_ = chrono::system_clock::now().time_since_epoch().count();
    }

    int slotNumber() {
        return slotNumber_;
    }
};
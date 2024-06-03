#include<iostream>

using namespace std;

enum Direction {
    UP = 0,
    DOWN
};

enum ElevatorStatus {
    Idle,
    Moving,
    OutOfService
};

class InRequest {
    int floorNum;
};

class OutRequest {
    int sourceFloor;
    Direction direction;
};

class Elevator {
    ElevatorStatus status_;
    Direction direction_;
    int currentFloor_;
    set<int> upRequests_;
    set<int> downRequests_;
    set<int> currRequests_;
    int endfloor;

public:
    Elevator(int currentFloor) : currentFloor_(currentFloor) {
        status = ElevatorStatus::Idle;
    }

    // getters, setters
    ElevatorStatus getStatus() {
        return status_;
    }

    void setStatus(ElevatorStatus status) {
        status_ = status;
    }

    Direction getDirection() {
        return direction_;
    }

    void setDirection(Direction direction) {
        direction_ = direction;
    }

    int getCurrentFloor() {
        return currentFloor_;
    }

    void setCurrentFloor(int currentFloor) {
        currentFloor_ = currentFloor;
    }

    set<int> getUpRequests() {
        return upRequests_;
    }

    void setUpRequests(set<int> upRequests) {
        upRequests_ = upRequests;
    }

    set<int> getDownRequests() {
        return downRequests_;
    }

    void setDownRequests(set<int> downRequests) {
        downRequests_ = downRequests;
    }

    set<int> getCurrRequests() {
        return currRequests_;
    }

    void setCurrRequests(set<int> currRequests) {
        currRequests_ = currRequests;
    }

    int getEndFloor() {
        return endfloor;
    }

    void setEndFloor(int endfloor) {
        endfloor_ = endfloor;
    }
};

class IElevatorStrategy {

public:
    virtual void processInRequest(InRequest request) = 0;
    virtual void processOutRequest(OutRequest request) = 0;
    virtual void processFloor(int currentFloor) = 0;
};

class ElevatorDirectionalStrategy : public IElevatorStrategy {
    void processInRequest(Elevator* elevator, InRequest request) {
        if(elevator_->getStatus() == ElevatorStatus::OutOfService) {
            return;
        }

        int floorNum = request.floorNum;
        elevator_->setStatus(ElevatorStatus::Moving);
        elevator_->currRequests.insert(floorNum);
        if(direction == UP && floorNum > elevator_->endFloor) {
            elevator_->endfloor = floorNum;
        } else if(direction == DOWN && floorNum < elevator_->endFloor) {
            elevator_->endfloor = floorNum;
        }
    }

    void processOutRequest(OutRequest request) {
        if(elevator_->getStatus == ElevatorStatus::OutOfService) {
            return;
        }

        int floorNum = request.sourceFloor;
        Direction direction = request.direction;
        elevator_->setStatus(ElevatorStatus::Moving);
        
        if(direction == Direction::UP) {
            if(floorNum > elevator_->currentFloor_) {
                elevator_->currequests.insert(floorNum);
            } else {
                elevator_->upRequests.insert(floorNum);
            }
        } else {
            if(floorNum < elevator_->currentFloor_) {
                elevator_->currRequests.insert(floorNum);
            } else {
                elevator_->downRequests.insert(floorNum);
            }
        }
    }

    void processFloor(int currentFloor) {

        elevator_->setCurrentFloor(currentFloor);

        if(currentFloor = elevator_ -> endFloor) {
            if(elevator_ -> upRequests.empty() && elevator_ -> downRequests.empty()) {
                elevator_->status = ElevatorStatus::Idle;
            } else {
                if(elevator_->direction == Direction::UP) {
                    elevator_->direction = Direction::DOWN;
                    elevator_->endfloor = *(elevator_->downRequests.begin());
                    elevator_->currRequests = elevator_->downRequests;
                    elevator_->downRewuests.clear();
                } else {
                    elevator_->direction = Direction::UP;
                    elevator_->endfloor = *(elevator_->upRequests.rbegin());
                    elevator_->currRequests = elevator_->upRequests;
                    elevator_->upRequests.clear();
                }
            }
        }
    }

}

class ElevatorManager {
    Elevator* elevator_;
    IElevatorStrategy* elevatorStrategy_;

public:
    ElevatorManager(Elevator* elevator, IElevatorStrategy elevatorStrategy*) : elevator_(elevator) {}
    void processInRequest(InRequest request) {
        elevatorStrategy_->processInRequest(request);
    }

    void processOutRequest(OutRequest request) {
        elevatorStrategy_->processOutRequest(request);
    }

    void processFloor(int currentFloor) {
        elevatorStrategy_->processFloor(currentFloor);
    }
};

class 

int main() {

    return 0;
}
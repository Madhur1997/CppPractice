#include<iostream>

using namespace std;

class APIController {
    OrderSubsystem* OrderSubsystem;
    DeliverySubsystem* DeliverySubsystem;
};

enum OrderStatus {
    PENDING,
    ACCEPTED,
    READY,
    DELIVERED,
    REJECTED
};

class PhoneNumber {
    static_assert(code >= 100 && code <= 999, "Invalid code");
    static_assert(number >= 1000000000 && number <= 9999999999, "Invalid number");
    int code;
    long int number;
public:
    PhoneNumber(int code, long int number) : code(code), number(number) {}
};

class Address {
    string street;
    string city;
    string state;
    string country;
    int pincode;
};

class RestaurantOrderRequest {
    vector<string> dishes;
    string specialRequests;
};

class Time {
    static_assert(hours >= 0 && hours <= 23, "Invalid hours");
    static_assert(minutes >= 0 && minutes <= 59, "Invalid minutes");
    static_assert(seconds >= 0 && seconds <= 59, "Invalid seconds");

    int hours;
    int minutes;
    int seconds;
public:
    Time(int hours, int minutes, int seconds) : hours(hours), minutes(minutes), seconds(seconds) {}
};

class RestaurantOrderResponse {
    OrderStatus status;
    Time eta;
};

class Restaurant {
    int id;
    string name;
    vector<Order> orders;
public:
    Restaurant(int id, string name) : id(id), name(name) {}
    RestaurantOrderResponse addOrder(RestaurantOrderRequest orderRequest) {
        // API call to Restaurant side zomato app.
        // Return Restaurant Order Response.
    }
};

// Singleton class
class RestaurantOrderSubsystem {
    static RestaurantOrderSubsystem* instance;
    RestaurantOrderSubsystem() = default;
    RestaurantOrderSubsystem(const RestaurantOrderSubsystem&) = delete;
    mutex mtx;
    unordered_map<int, Restaurant*> restaurants;
public:
    static RestaurantOrderSubsystem* getInstance() {
        if(instance == nullptr) {
            mtx.lock();
            if(instance == nullptr) {
                instance = new RestaurantOrderSubsystem();
            }
        }
        return instance;
    }

    RestaurantOrderResponse putOrder(int restaurantId, RestaurantOrderRequest orderRequest) {
        Restaurant* restaurant = getRestaurant();
        return restaurant->addOrder(orderRequest);
    }

    Restaurant getRestaurant(int restaurantId, RestaurantOrderRequest orderRequest) {
        return restaurants[restaurantId];
    }
};

class DeliveryOrderRequest {
    Customer customer;
    Address deliveryAddress;
    Restaurant restaurant;
}

class Rider {
    int id;
    string name;
    priority_queue<Order> orderQueue;
    PhoneNumber phoneNumber;
public:
    Rider(int id, string name, PhoneNumber PhoneNumber) : id(id), name(name), phoneNumber(phoneNumber) {}
    bool acceptOrder() {

    }
};

class IRiderMatchingStrategy {
public:
    virtual vector<Rider*> getMatchingRiders(DeliveryOrderRequest orderRequest, vector<Rider*> riders) = 0;
};

class LocationRiderMatching : public IRiderMatchingStrategy {
public:
    vector<Rider*> getMatchingRiders(DeliveryOrderRequest orderRequest, vector<Rider*> riders) override {
        // Find the rider based on the restaurant location, rider locations.
    }
};

class RiderMatchingStrategyFactory {
public:
    static IRiderMatchingStrategy getStrategy() {
        // based on customer id, customer rating, return IRiderMatchingStrategy
        return new LocationRiderMatching();
    }
};  

// Singleton class
class DeliverySubsystem {
    static DeliverySubsystem* instance;
    DeliverySubsystem() = default;
    DeliverySubsystem(const DeliverySubsystem&) = delete;
    mutex mtx;
    unordered_map<Rider
public:
    static DeliverySubsystem* getInstance() {
        if (instance == nullptr) {
            mtx.lock();
            if(instance == nullptr) {
                instance = new DeliverySubsystem();
            }
        }
        return instance;
    }

    Rider* matchRider(DeliveryOrderRequest orderRequest) {
        // Find the rider based on the orderRequest.
        IRiderMatchingStrategy strategy = RiderMatchingStrategyFactory::getStrategy();
        vector<Rider*> riders = strategy->getMatchingRiders(orderRequest, riders);

    }
};

int main() {

    return 0;
}
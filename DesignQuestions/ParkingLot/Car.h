#include<string>

using namespace std;

class Car {
    string registrationNumber_;
    string color_;
public:
    Car(string registrationNumber, string color) : registrationNumber_(registrationNumber), color_(color) {}
    string color();
};
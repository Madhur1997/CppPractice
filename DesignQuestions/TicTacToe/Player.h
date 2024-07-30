#include<string>
#include "Enums.h"


class Player {
    string name_;
    Symbol symbol_;
public:
    Player(string name, Symbol symbol) : name_(name), symbol_(symbol) {}

    string name() {
        return name_;
    }
};

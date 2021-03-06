//
// Created by bnorb on 27.01.20.
//

#pragma once

#include "Item.hpp"
//#include "Inventory.hpp"
#include <chrono>

class Inventory;    // Avoid cyclic dependencies
class EstusFlask {
public:
    EstusFlask();
    ~EstusFlask();
    bool canUse();
    bool canReset();
    void use(Inventory& inventory);
    void reset(Inventory& inventory);
    int usages;

private:
    Item item;
    int cooldown = 250;     //ms
    std::chrono::high_resolution_clock::time_point lastUse;
    std::chrono::high_resolution_clock::time_point lastReset;
};

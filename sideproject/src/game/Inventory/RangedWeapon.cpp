//
// Created by bnorb on 26.01.20.
//

#include "RangedWeapon.hpp"
#include <string>

RangedWeapon::RangedWeapon(std::string& name, std::string& imagePath, int value)
    : Item(name, imagePath, value)
    , damage(10)
    , range(10)
    , cooldown(250)     // ms
    , bulletQuantity(5)
    , bulletSpeed(10)
{}

RangedWeapon::~RangedWeapon() = default;
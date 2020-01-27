//
// Created by bnorb on 26.01.20.
//

#include "RangedWeaponOld.hpp"
#include <string>

RangedWeaponOld::RangedWeaponOld(std::string& name, std::string& imagePath, int value)
    : ItemOld(name, imagePath, value)
    , damage(10)
    , range(10)
    , cooldown(250)     // ms
    , bulletQuantity(5)
    , bulletSpeed(10)
{}

RangedWeaponOld::~RangedWeaponOld() = default;
//
// Created by bnorb on 26.01.20.
//

#pragma once

#include "ItemOld.hpp"

class RangedWeaponOld : public ItemOld{
public:
    RangedWeaponOld(std::string& name, std::string& imagePath, int value);
    ~RangedWeaponOld();

private:
    int damage;
    int range;
    int cooldown;
    int bulletQuantity;
    int bulletSpeed;
};


//
// Created by bnorb on 26.01.20.
//

#pragma once

#include "Item.hpp"

class RangedWeapon : public Item{
public:
    RangedWeapon(std::string& name, std::string& imagePath, int value);
    ~RangedWeapon();

private:
    int damage;
    int range;
    int cooldown;
    int bulletQuantity;
    int bulletSpeed;
};


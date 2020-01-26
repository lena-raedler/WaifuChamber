//
// Created by bnorb on 26.01.20.
//

#pragma once

#include "Slot.hpp"
#include "../utils/utility.h"
#include <memory>
#include "Item.hpp"


class Inventory {
public:
    Inventory();
    explicit Inventory(Renderer& renderer);
    ~Inventory();
    void renderInventory();

private:
    Slot rangedWeaponSlot, slot2, slot3, slot4, slot5, slot6;
    Item rangedWeapon;
    Renderer* renderer;
};
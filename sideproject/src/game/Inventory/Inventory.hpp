//
// Created by bnorb on 27.01.20.
//

#pragma once

#include "Slot.hpp"
#include "../utils/renderer.h"
#include "EstusFlask.hpp"


class Inventory {
public:
    Inventory();
    Inventory(Renderer& renderer);
    ~Inventory();
    void renderInventory();
    Slot rangedWeaponSlot, slot2, slot3, slot4, slot5, estusFlaskSlot;
    EstusFlask estusFlask;

private:
    Renderer* renderer;
};
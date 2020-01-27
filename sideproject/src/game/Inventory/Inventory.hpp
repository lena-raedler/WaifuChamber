//
// Created by bnorb on 27.01.20.
//

#pragma once

#include "Slot.hpp"
#include "../utils/renderer.h"


class Inventory {
public:
    Inventory();
    Inventory(Renderer& renderer);
    ~Inventory();
    void renderInventory();

private:
    Slot slot1, slot2, slot3, slot4, slot5, slot6;
    Renderer* renderer;
};
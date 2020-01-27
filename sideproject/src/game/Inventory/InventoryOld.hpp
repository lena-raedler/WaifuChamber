//
// Created by bnorb on 26.01.20.
//

#pragma once

#include "SlotOld.hpp"
#include "../utils/utility.h"
#include <memory>
#include "ItemOld.hpp"


class InventoryOld {
public:
    InventoryOld();
    explicit InventoryOld(Renderer& renderer);
    ~InventoryOld();
    void renderInventory();

private:
    SlotOld rangedWeaponSlot, slot2, slot3, slot4, slot5, slot6;
    ItemOld rangedWeapon;
    Renderer* renderer;
};
//
// Created by bnorb on 26.01.20.
//

#include "Inventory.hpp"

Inventory::Inventory() = default;

Inventory::Inventory(Renderer& renderer)
    : rangedWeaponSlot("files/textures/weapons/bow_01.png", renderer, Vec2<int> {50, 60} )
    , slot2("files/textures/weapons/bow_01.png", renderer, Vec2<int> {90, 60} )
    , slot3("files/textures/weapons/Arrow.png", renderer, Vec2<int> {130, 60} )
    , slot4("files/textures/weapons/Arrow.png", renderer, Vec2<int> {170, 60} )
    , slot5("files/textures/weapons/Arrow.png", renderer, Vec2<int> {210, 60} )
    , slot6("files/textures/weapons/Arrow.png", renderer, Vec2<int> {250, 60} )
    , renderer(&renderer)
{
    rangedWeaponSlot.setAvailable(true);
}

Inventory::~Inventory() = default;

void Inventory::renderInventory() {
    rangedWeaponSlot.renderSlot();
    slot2.renderSlot();
    slot3.renderSlot();
    slot4.renderSlot();
    slot5.renderSlot();
    slot6.renderSlot();
}
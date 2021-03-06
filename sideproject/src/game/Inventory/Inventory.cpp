//
// Created by bnorb on 27.01.20.
//

#include "Inventory.hpp"

Inventory::Inventory() = default;

Inventory::Inventory(Renderer& renderer)
        : rangedWeaponSlot(Item("Standard Crossbow", "files/textures/weapons/bow_01.png", 10), renderer, Vec2<int> {64, 112})
        , slot2(renderer, Vec2<int> {104, 112})
        , slot3(renderer, Vec2<int> {144, 112})
        , slot4(renderer, Vec2<int> {184, 112})
        , slot5(renderer, Vec2<int> {224, 112})
        , estusFlaskSlot(Item("Estus Flask", "files/textures/estusFlask/estus_flask.png", 10), renderer, Vec2<int> {264, 112})
        , estusFlask()
        , renderer(&renderer)
{}

Inventory::~Inventory() = default;

void Inventory::renderInventory() {
    rangedWeaponSlot.renderSlot();
    slot2.renderSlot();
    slot3.renderSlot();
    slot4.renderSlot();
    slot5.renderSlot();
    estusFlaskSlot.renderSlot();
}
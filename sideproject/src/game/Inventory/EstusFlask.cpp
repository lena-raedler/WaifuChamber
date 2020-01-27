//
// Created by bnorb on 27.01.20.
//

#include "EstusFlask.hpp"
#include "Inventory.hpp"

EstusFlask::EstusFlask()
    : usages(3)
    , item("Estus Flask", "files/textures/estusFlask/estus_flask.png", 9001)
    , lastUse(std::chrono::high_resolution_clock::now())
{}

EstusFlask::~EstusFlask() = default;

bool EstusFlask::canUse() {
    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastUse = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastUse);
    return usages > 0 && timeSinceLastUse > std::chrono::milliseconds(cooldown);
}

void EstusFlask::use(Inventory& inventory) {
    lastUse = std::chrono::high_resolution_clock::now();
    if (--usages <= 0) {
        item.imagePath = "files/textures/estusFlask/estus_flask_empty.png";
        inventory.estusFlaskSlot.loadNewItemImage("files/textures/estusFlask/estus_flask_empty.png");
    }
}

bool EstusFlask::canReset() {
    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastReset = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastReset);
    return timeSinceLastReset > std::chrono::milliseconds(cooldown);
}

void EstusFlask::reset(Inventory& inventory) {
    usages = 3;
    item.imagePath = "files/textures/estusFlask/estus_flask.png";
    inventory.estusFlaskSlot.loadNewItemImage("files/textures/estusFlask/estus_flask.png");
}
//
// Created by auki on 26.01.20.
//

#ifndef WAIFU_ABILITY_H
#define WAIFU_ABILITY_H


#include "../../utils/Vec2.h"
#include "Projectile.hpp"
#include "../../GlobalObjects.h"
#include <chrono>
#include <utility>

class Ability {
public:
    bool aimed = true;
    vec_t origin = {0, 0};
    std::vector<Projectile> projectiles;
    int cooldown = 250;
    double speed;
    std::chrono::high_resolution_clock::time_point lastUsed  = std::chrono::high_resolution_clock::now();
    bool isAvail();
    void use(vec_t pos);
};


#endif //WAIFU_ABILITY_H

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
    Ability() = default;
    Ability(Ability& o)=default;
    Ability(Ability&& o) = default;
    Ability(Projectile p, bool aimed, double speed, vec_t origin, int cooldown);
    bool aimed;
    vec_t origin;
    Projectile projectile;
    int cooldown;
    double speed;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastUsed = std::chrono::high_resolution_clock::now();
    bool isAvail();
    void use(vec_t pos);
};


#endif //WAIFU_ABILITY_H

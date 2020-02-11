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
    vec_t aimOffset;
    std::vector<Projectile> projectiles;
    double cooldown = 2.5;
    double speed;
    double lastUsed  = 0;
    void useIfAvail(double delta, vec_t& pos);
    bool isAvail(double delta);
    void use(vec_t pos);
};


#endif //WAIFU_ABILITY_H

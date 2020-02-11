//
// Created by auki on 11.02.20.
//
#include "../../utils/Vec2.h"
#include "Projectile.hpp"
#include "../../GlobalObjects.h"
#include "SoundEffect.h"
#include <chrono>
#include <utility>
#include "TelegraphedAttack.h"

#ifndef WAIFU_TELEGRAPHEDABILITY_H
#define WAIFU_TELEGRAPHEDABILITY_H


class TelegraphedAbility {
public:
    bool aimed = true;
    vec_t origin = {GlobalConstants::tileSize/2, GlobalConstants::tileSize/2};
    vec_t aimOffset;
    std::vector<TelegraphedAttack> attack;
    double cooldown = 2.5;
    double speed = 20;
    SoundEffect soundUse;
    double lastUsed  = 0;
    void useIfAvail(double delta, vec_t& pos);
    bool isAvail(double delta);
    void use(vec_t pos);

};


#endif //WAIFU_TELEGRAPHEDABILITY_H

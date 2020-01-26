//
// Created by auki on 26.01.20.
//

#ifndef WAIFU_ENEMY_H
#define WAIFU_ENEMY_H

#include "Movable.h"
#include "player.h"
#include "Ability.h"

class Enemy : public Movable{
public:
    int maxhealth = 1;
    int health = maxhealth;
    double speed;
    std::vector<Ability> abilities;
    std::vector<double> probability;

    void upkeep(double delta);
};


#endif //WAIFU_ENEMY_H

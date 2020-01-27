//
// Created by auki on 26.01.20.
//

#ifndef WAIFU_ENEMY_H
#define WAIFU_ENEMY_H

#include "Movable.h"
#include "player.h"
#include "Ability.h"

enum Behaviour{CHASE, STATIONARY, FLEE, PATROL};

class Enemy : public Movable{
public:
    int maxHealth = 1;
    int health = maxHealth;
    double speed;
    std::vector<Ability> abilities;
    std::vector<double> probability;
    Behaviour ai;

    void setMaxHealth(int i);
    void getHit(double d);

    void upkeep(double delta);
};


#endif //WAIFU_ENEMY_H

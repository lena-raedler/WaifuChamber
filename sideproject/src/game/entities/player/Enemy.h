//
// Created by auki on 26.01.20.
//

#ifndef WAIFU_ENEMY_H
#define WAIFU_ENEMY_H
#include "../../SavedVariables.h"
#include "Movable.h"
#include "player.h"
#include "Ability.h"
#include "TelegraphedAbility.h"

enum Behaviour{CHASE, STATIONARY, FLEE, PATROL, CONSTANT};

class Enemy : public Movable{
public:
    int maxHealth = 1;
    int health = maxHealth;
    int souls;
    double speed = 10;
    std::vector<Ability> abilities;
    std::vector<TelegraphedAbility> telegraphedAbilities;
    std::vector<double> probability;

    Behaviour ai = CONSTANT;
    int damageOnTouch = 0;
    std::vector<vec_t> patrolPoints;
    size_t patrolCounter = 0;
    void setMaxHealth(int i);
    void getHit(double d);
    void kill();
    void chase(double d);
    void flee(double d);

    void upkeep(double delta);
};


#endif //WAIFU_ENEMY_H

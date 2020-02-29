//
// Created by auki on 26.01.20.
//

#ifndef WAIFU_ENEMY_H
#define WAIFU_ENEMY_H
#include "../../SavedVariables.h"
#include "../../utils/renderer.h"
#include "Movable.h"
#include "player.h"
#include "Ability.h"
#include "TelegraphedAbility.h"
#include "Sprites.h"
#include "Bar.hpp"

enum Behaviour{CHASE, STATIONARY, FLEE, PATROL, CONSTANT, CHASEXY};

class Enemy : public Movable{
public:
    int maxHealth = 1;
    int health = maxHealth;
    Bar healthBar;
    int healthBarOffset = 2;
    int souls = 100;
    double speed = 10;
    std::vector<Ability> abilities;
    std::vector<TelegraphedAbility> telegraphedAbilities;
    std::vector<double> probability;
    bool hasSprite = true;
    Sprites enemySprite;

    Behaviour ai = CONSTANT;
    statuseffect statusOnTouch;
    int damageOnTouch = 0;
    std::vector<vec_t> patrolPoints;
    size_t patrolCounter = 0;
    void setMaxHealth(int i);
    void getHit(double d);
    void kill();
    void chase(double d);
    void flee(double d);

    void upkeep(double delta);
    double healthPercentage(){return (double) health / maxHealth;}

    //overriding functions from movable
    void init(Renderer& renderer);
    void render(Renderer& renderer);
};


#endif //WAIFU_ENEMY_H

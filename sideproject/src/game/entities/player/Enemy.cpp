//
// Created by auki on 26.01.20.
//

#include "Enemy.h"

void Enemy::upkeep(double delta){
    move(delta);
    for(Ability& a : abilities){
        if(a.isAvail()){
            a.use(position);
        }
    }
}
void Enemy::setMaxHealth(int i) {
    maxHealth = i;
    health = i;
}

void Enemy::getHit(double d){
    health -= d;
}

void Enemy::kill(){
    //dostuff
}
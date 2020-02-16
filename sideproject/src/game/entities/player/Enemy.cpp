//
// Created by auki on 26.01.20.
//

#include "Enemy.h"

void Enemy::upkeep(double delta){
    vec_t playerPos = GlobalObjects::playerPtr->position;
    switch(ai){
        case CHASE:
            velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
            velocity.x *=speed;
            break;
        case STATIONARY:
            velocity = {0, 0};
            break;
        case FLEE:
            velocity.x = std::clamp(position.x - playerPos.x, -1.0, 1.0);
            velocity.x *=speed;
            break;
        case PATROL:
            if(patrolPoints.size() > 0) {
                if (std::abs(position.x - patrolPoints[patrolCounter].x) < GlobalConstants::epsilon) {
                    if (!(++patrolCounter < patrolPoints.size())) {
                        patrolCounter = 0;
                    }
                }
                velocity.x = std::clamp(patrolPoints[patrolCounter].x - position.x, -1.0, 1.0);
                velocity.x *= speed;
            }
            break;
        case CONSTANT:
            break;
        default:
            break;
    }
    move(delta);

    for(Ability& a : abilities){
        a.useIfAvail(delta, position);
        a.lastUsed -= delta;
    }
    for(auto& a: telegraphedAbilities){
        a.useIfAvail(delta, position);
        a.lastUsed -= delta;
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
    GlobalObjects::savedVariables.souls += souls;
    std::cout << "Souls: " << GlobalObjects::savedVariables.souls << std::endl;
    SDL_DestroyTexture(texture);
    //dostuff
}
void Enemy::chase(double d){
    vec_t playerPos = GlobalObjects::playerPtr->position;
    velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
    velocity.x *=speed;

}
void Enemy::flee(double d){
    vec_t playerPos = GlobalObjects::playerPtr->position;
    velocity.x = std::clamp(position.x - playerPos.x, -1.0, 1.0);
    velocity.x *=speed;

}
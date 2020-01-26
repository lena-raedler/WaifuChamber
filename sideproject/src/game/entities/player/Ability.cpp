//
// Created by auki on 26.01.20.
//

#include "Ability.h"

bool Ability::isAvail() {
    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastUse = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastUsed);
    if(timeSinceLastUse >  std::chrono::milliseconds(cooldown)){
        return true;
    }
    return false;
}

void Ability::use(vec_t pos) {
    vec_t tmp;
    lastUsed = std::chrono::high_resolution_clock::now();
    pos += origin;
    if(aimed){
        tmp = GlobalObjects::playerPtr->position - pos;
        tmp.normalize();
        tmp *= speed;
        projectile.velocity = tmp;
        GlobalObjects::projectiles.push_back(projectile);


    } else{
        tmp = pos;//TODO
    }


}

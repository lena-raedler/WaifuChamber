//
// Created by auki on 26.01.20.
//

#include "Ability.h"

bool Ability::isAvail() {
    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastUse = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastUsed);
    return timeSinceLastUse > std::chrono::milliseconds(cooldown);
}

void Ability::use(vec_t pos) {
    vec_t tmp;

    pos += origin;
    if(aimed){
        tmp = GlobalObjects::playerPtr->position - pos;
        tmp.normalize();
        tmp *= speed;

        projectile.position = pos + origin;
        projectile.velocity = tmp;
        {
            SDL_Rect r = {(int)projectile.position.x, (int)projectile.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
            projectile.rec = std::make_shared<SDL_Rect>(r);
        }
        GlobalObjects::projectiles.push_back(projectile);


    } else{
        tmp = pos;//TODO
    }
    lastUsed = std::chrono::high_resolution_clock::now();


}

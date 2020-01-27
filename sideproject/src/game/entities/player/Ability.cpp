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
        GlobalObjects::projectiles.push_back(projectile);


    } else{
        tmp = pos;//TODO
    }

    switch (projectile.owner) {
        case HOSTILE:
            break;
        case PLAYER:
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            vec_t vec {static_cast<double>(mouse_x), static_cast<double>(mouse_y)};
            tmp = vec - pos;
            tmp.normalize();
            tmp *= speed;

            //projectile.position = pos + origin;
            projectile.position = pos;
            projectile.velocity = tmp;
            GlobalObjects::projectiles.push_back(projectile);
            break;
    }

    lastUsed = std::chrono::high_resolution_clock::now();


}

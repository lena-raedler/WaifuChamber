//
// Created by auki on 26.01.20.
//

#include "Ability.h"

bool Ability::isAvail(double delta) {
    lastUsed -= delta;
    if (lastUsed < 0){
        lastUsed = cooldown;
        return true;
    }
    return false;
}

void Ability::use(vec_t pos) {
    pos = pos + origin;
    vec_t tmp;

    for(Projectile projectile : projectiles) {
        switch (projectile.owner) {
            case HOSTILE:
                if (aimed) {
                    tmp = GlobalObjects::playerPtr->position - pos;
                    tmp.normalize();
                    tmp *= speed;

                    projectile.position = pos + origin;
                    projectile.velocity += tmp;
                    {
                        SDL_Rect r = {(int) projectile.position.x, (int) projectile.position.y, GlobalConstants::tileSize,
                                      GlobalConstants::tileSize};
                        projectile.rec = std::make_shared<SDL_Rect>(r);
                    }



                } else {
                    projectile.position = pos + origin;//todo fix double addition
                    projectile.velocity.normalize();
                    projectile.velocity *=speed;
                }
                GlobalObjects::projectiles.push_back(std::make_shared<Projectile>(projectile));
                break;  // Soon (tm)
            case PLAYER:
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                vec_t vec{static_cast<double>(mouse_x), static_cast<double>(mouse_y)};
                tmp = (vec - pos) - vec_t{GlobalConstants::tileSize / 2, GlobalConstants::tileSize / 2};
                tmp.normalize();
                tmp *= speed;

                //projectile.position = pos + origin;
                projectile.position = pos;
                projectile.velocity = tmp;
                {
                    SDL_Rect r = {(int) projectile.position.x, (int) projectile.position.y, GlobalConstants::tileSize,
                                  GlobalConstants::tileSize};
                    projectile.rec = std::make_shared<SDL_Rect>(r);
                }
                GlobalObjects::projectiles.push_back(std::make_shared<Projectile>(projectile));
                break;
        }
    }
}

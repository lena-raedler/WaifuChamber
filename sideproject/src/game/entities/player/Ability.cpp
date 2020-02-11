//
// Created by auki on 26.01.20.
//

#include "Ability.h"

void Ability::useIfAvail(double delta, vec_t& pos){
    if(isAvail(delta)){
        use(pos);
        soundUse.play();
    }
}
bool Ability::isAvail(double delta) {
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
        projectile.position = pos;
        switch (projectile.owner) {
            case HOSTILE:
                if (aimed) {
                    tmp = GlobalObjects::playerPtr->position - pos;
                    tmp.normalize();
                    tmp *= speed;


                    projectile.velocity += tmp;
                    {
                        SDL_Rect r = {(int) projectile.position.x, (int) projectile.position.y, GlobalConstants::tileSize,
                                      GlobalConstants::tileSize};
                        projectile.rec = std::make_shared<SDL_Rect>(r);
                    }



                } else {
                    projectile.velocity.normalize();
                    projectile.velocity *=speed;
                }
                GlobalObjects::projectiles.push_back(std::make_shared<Projectile>(projectile));

                break;  // Soon (tm)
            case PLAYER:
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                vec_t vec{static_cast<double>(mouse_x), static_cast<double>(mouse_y)};
                tmp = (vec - pos);
                tmp.normalize();
                tmp *= speed;


                projectile.velocity = tmp;
                {
                    SDL_Rect r = {(int) projectile.position.x, (int) projectile.position.y, GlobalConstants::tileSize,
                                  GlobalConstants::tileSize};
                    projectile.rec = std::make_shared<SDL_Rect>(r);
                }
                GlobalObjects::projectiles.push_back(std::make_shared<Projectile>(projectile));
                std::cout << GlobalObjects::projectiles.size() << std::endl;
                break;
        }
    }
}

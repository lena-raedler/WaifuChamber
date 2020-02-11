//
// Created by auki on 27.01.20.
//

#include "EnemyBuilder.h"
namespace EnemyBuilder {
    void buildEnemy(std::vector<std::shared_ptr<Enemy>>& vece, int id, std::pair<int, int> pos){//hardcoded because fuck that shit
        Enemy e;
        Projectile p;
        Ability a;
        statuseffect s;
        switch(id){
            case 1: //Skelly
                e.position = utility::convert(pos);
                e.velocity = {0,0};
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = FLEE;
                e.gravityType = NORMAL;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                p.damage = 20;
                p.timeToLive = 100;
                p.usesPlatforms = false;
                p.fragile = false;
                p.gravityType = NOGRAVITY;
                p.baseInit();

                s.type = BLEED;
                s.intensity = 100;

                p.status = s;

                a.projectiles.push_back(p);
                a.speed = 20;
                a.cooldown = 10;

                e.abilities.push_back(a);
                e.textureLocation = "files/textures/skeleton_01.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                break;
            case 2://floating skelly
                e.position = utility::convert(pos);
                e.velocity = {0,0};
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = PATROL;
                e.gravityType = NOGRAVITY;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                p.damage = 20;
                p.timeToLive = 100;
                p.usesPlatforms = false;
                p.fragile = false;
                p.gravityType = NOGRAVITY;
                p.baseInit();

                a.projectiles.push_back(p);
                a.speed = 20;
                a.cooldown = 10;

                e.abilities.push_back(a);
                e.textureLocation = "files/textures/skeleton_01.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                break;
            case 3: //spikes
                e.position = utility::convert(pos);
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = STATIONARY;
                e.gravityType = NOGRAVITY;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                e.iframes = true;
                e.damageOnTouch = 70;
                e.textureLocation = "files/textures/skeleton_01.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }

                break;
            case 4: //spikes
                e.position = utility::convert(pos);
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = PATROL;
                e.gravityType = NOGRAVITY;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                e.iframes = true;
                e.damageOnTouch = 70;
                e.textureLocation = "files/textures/skeleton_01.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }

                break;
            default:
                break;
        }
        GlobalObjects::enemies.push_back(std::make_shared<Enemy>(e));
    };

};
//
// Created by auki on 27.01.20.
//

#include "EnemyBuilder.h"
namespace EnemyBuilder {
    void buildEnemy(std::vector<Enemy>& vece, int id, std::pair<int, int> pos){//hardcoded because fuck that shit
        Enemy e;
        Projectile p;
        Ability a;
        switch(id){
            case 1: //Skelly
                e.position = utility::convert(pos);
                e.velocity = {0,0};
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = PATROL;
                e.gravityType = NORMAL;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                p.damage = 20;
                p.timeToLive = 10000;
                p.usesPlatforms = false;
                p.fragile = true;
                p.gravityType = NOGRAVITY;
                p.baseInit();

                a.projectiles.push_back(p);
                a.speed = 20;
                a.cooldown = 1000;

                e.abilities.push_back(a);
                e.textureLocation = "files/textures/skeleton_01.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {pos.first, pos.second, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                GlobalObjects::enemies.push_back(e);
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
                p.timeToLive = 10000;
                p.usesPlatforms = false;
                p.fragile = true;
                p.gravityType = NOGRAVITY;
                p.baseInit();

                a.projectiles.push_back(p);
                a.speed = 20;
                a.cooldown = 1000;

                e.abilities.push_back(a);
                e.textureLocation = "files/textures/skeleton_01.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {pos.first, pos.second, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                GlobalObjects::enemies.push_back(e);
            default:
                break;
        }
    };

};
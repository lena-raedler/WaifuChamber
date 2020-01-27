//
// Created by auki on 27.01.20.
//

#ifndef WAIFU_ENEMYBUILDER_H
#define WAIFU_ENEMYBUILDER_H
#include "Enemy.h"
#include <vector>

namespace EnemyBuilder {
    void buildEnemy(std::vector<Enemy>& vece, int id, std::pair<int, int> pos){//hardcoded because fuck that shit
        Enemy e;
        Projectile p;
        Ability a;
        switch(id){
            case 1: //Skelly
            e.position = utility::convert(pos);
            e.setMaxHealth(10);
            e.speed = 10;
            e.ai = PATROL;
            e.gravityType = NORMAL;
            utility::fillDefaultHitbox(e.hitbox);

            utility::fillDefaultHitbox(p.hitbox);
            p.damage = 20;
            p.timeToLive = 1000;
            p.usesPlatforms = false;
            p.baseInit();

            a.projectile = p;
            a.speed = 20;
            a.cooldown = 1000;

            e.abilities.push_back(a);

            //todo fill rec
            GlobalObjects::enemies.push_back(e);
            break;
            default:
                break;
        }
    };

};


#endif //WAIFU_ENEMYBUILDER_H

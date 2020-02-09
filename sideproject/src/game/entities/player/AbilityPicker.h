//
// Created by auki on 09.02.20.
//

#ifndef WAIFU_ABILITYPICKER_H
#define WAIFU_ABILITYPICKER_H


#include "Ability.h"
enum AbilitySet{
    PL_RANGED,
    PL_MELEE,
    NPC_RANGED,
    NPC_MELEE,
    BOSS_RANGED,
    BOSS_MELEE
};
namespace AbilityPicker {

    void plRanged(int i, Ability& a){
        Projectile p;
        switch(i){
            case 0: //default shot

                utility::fillDefaultHitbox(p.hitbox);
                p.damage = 20;
                p.timeToLive = 2000;
                p.usesPlatforms = false;
                p.fragile = false;
                p.gravityType = NOGRAVITY;
                p.owner = PLAYER;
                p.baseInit();

                a.projectiles.push_back(p);
                a.speed = 47;
                a.cooldown = 1000;
                //a.origin = {0, 0};
                a.aimed = false;
                break;
            default:
                break;
        }

    }
    void plMelee(int i, Ability& a){

    }
    void npcRanged(int i, Ability& a){

    }
    void npcMelee(int i, Ability& a){

    }
    void bossRanged(int i, Ability& a){

    }
    void bossMelee(int i, Ability& a){

    }
    void pickAbility(Ability& a, int i, AbilitySet set){
        switch(set){
            case PL_RANGED:
                plRanged(i, a);
                break;
            case PL_MELEE:
                plMelee(i,a);
                break;
            case NPC_RANGED:
                npcRanged(i, a);
                break;
            case NPC_MELEE:
                npcMelee(i,a);
                break;
            case BOSS_RANGED:
                bossRanged(i, a);
                break;
            case BOSS_MELEE:
                bossMelee(i,a);
            default:break;
        }
    }

};


#endif //WAIFU_ABILITYPICKER_H

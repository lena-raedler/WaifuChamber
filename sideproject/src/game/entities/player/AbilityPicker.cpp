//
// Created by auki on 12.02.20.
//
#include "AbilityPicker.h"
#include "TelegraphedAbility.h"


template <class T>
void AbilityPicker<T>::plRanged(int i, T& a){
    SoundEffect s;
    Projectile p;
    p.textureLocation = "files/textures/weapons/Arrow.png";
    switch(i){
        case 0: //default shot

            utility::fillDefaultHitbox(p.hitbox, 1,1, {-GlobalConstants::tileSize/2, -GlobalConstants::tileSize/2});
            //utility::fillDefaultHitbox(p.hitbox, 1,1, {0, 0});
            p.damage = 20;
            p.timeToLive = 2000;
            p.usesPlatforms = false;
            p.fragile = true;
            p.gravityType = NOGRAVITY;
            p.terminalVelocity = {200, 200};
            p.owner = PLAYER;

            // Doesn't change the texture position for some reason...
            p.position.x -= GlobalConstants::tileSize/2;;
            p.position.y -= GlobalConstants::tileSize/2;
            p.init();
            p.rec->x -= GlobalConstants::tileSize/2;
            p.rec->y -= GlobalConstants::tileSize/2;

            a.soundUse.load("smb_fireball.wav");
            a.addProjectile(p);
            a.speed = 47;
            a.lastUsed= 4;
            a.cooldown = 4;
            a.origin = {GlobalConstants::tileSize/2, GlobalConstants::tileSize/2};
            a.aimOffset = a.origin;
            a.aimed = false;
            break;
        default:
            break;
    }

}
template <class T>
void AbilityPicker<T>::plMelee(int i, T& a){

}
template <class T>
void AbilityPicker<T>::npcRanged(int i, T& a){
    Projectile p;
    TelegraphedAttack attack;
    statuseffect s;
    p.textureLocation = "textures/weapons/Arrow.png";
    switch(i){
        case 1: // telegraphed beam 4xscreenheight
            attack.damage = 20;
            attack.aimed = 1;
            attack.maxTime = 20;
            attack.set(GlobalObjects::playerPtr->position.x-32, 32, 64, 1000);
            a.cooldown = 20;
            a.lastUsed = 20;
            a.addAttack(attack);
            break;
        default:
            break;
    }

}
template <class T>
void AbilityPicker<T>::npcMelee(int i, T& a){

}
template <class T>
void AbilityPicker<T>::bossRanged(int i, T& a){
    Projectile p;
    TelegraphedAttack attack;
    statuseffect s;
    p.textureLocation = "textures/weapons/Arrow.png";
    switch(i){
        case 1: //lazor
            p.gravityType = NOGRAVITY;
            p.usesPlatforms = false;
            p.damage = 20;
            p.fragile = true;
            s.type = SHOCK;
            s.intensity = 40;
            p.status.push_back(s);
            utility::fillDefaultHitbox(p.hitbox);
            p.timeToLive = 12;
            p.velocity = {0, 0};
            p.init();
            a.addProjectile(p);
            a.speed = 30;
            a.cooldown = 10;
            a.origin = {GlobalConstants::tileSize / 2, GlobalConstants::tileSize / 2};
            break;
        case 2: // aoe blast

            s.type = SHOCK;
            s.intensity = 60;
            p.status.push_back(s);
            p.gravityType = NOGRAVITY;
            p.usesPlatforms = false;
            p.fragile = false;
            p.damage = 40;
            p.timeToLive = 20;
            p.init();
            utility::fillDefaultHitbox(p.hitbox);
            a.speed = 40;
            a.cooldown = 100;
            a.origin = {GlobalConstants::tileSize/2, GlobalConstants::tileSize/2};
            a.aimed = false;
            for(int i = -1; i < 2; ++i){
                for(int j = -1; j < 2;++j){
                    if (i == 0 && j == 0){
                        continue;
                    }
                    p.velocity = {(double)i, (double)j};
                    a.addProjectile(p);
                }
            }
            break;
        case 3: // telegraphed beam 4xscreenheight
            attack.damage = 20;
            attack.aimed = 1;
            attack.maxTime = 20;
            attack.set(GlobalObjects::playerPtr->position.x-32, 32, 64*4, 1000);
            a.cooldown = 200;
            a.lastUsed = 200;
            a.addAttack(attack);
            break;
        case 4://bleed bullets
            p.gravityType = NOGRAVITY;
            p.usesPlatforms = false;
            p.damage = 10;
            p.fragile = false;
            s.type = BLEED;
            s.intensity = 60;
            p.status.push_back(s);
            utility::fillDefaultHitbox(p.hitbox);
            p.timeToLive = 12;
            p.velocity = {0, 0};
            p.init();
            a.addProjectile(p);
            a.speed = 50;
            a.cooldown = 40;
            break;
        case 5://shock bullets
            p.gravityType = NOGRAVITY;
            p.usesPlatforms = false;
            p.damage = 15;
            p.fragile = false;
            p.status.push_back(s);
            utility::fillDefaultHitbox(p.hitbox);
            p.timeToLive = 12;
            p.velocity = {0, 0};
            p.init();
            a.addProjectile(p);
            a.speed = 50;
            a.cooldown = 50;
            break;
        case 6:
            attack.damage = 80;
            attack.aimed = 1;
            attack.maxTime = 20;
            attack.set(GlobalObjects::playerPtr->position.x-16, 32, 64, 1000);
            a.cooldown = 20;
            a.lastUsed = 20;
            a.addAttack(attack);
            break;
        case 7:
            attack.damage = 40;
            attack.aimed = 3;
            attack.maxTime = 12;
            attack.set(0, GlobalObjects::playerPtr->position.y, 1000, 64);
            a.cooldown = 45;
            a.lastUsed = 45;
            a.addAttack(attack);
            break;
        case 8:
            s.type = BLEED;
            s.intensity = 90;
            p.status.push_back(s);
            p.gravityType = NORMAL;
            p.usesPlatforms = false;
            p.fragile = false;
            p.damage = 40;
            p.timeToLive = 20;
            p.init();
            utility::fillDefaultHitbox(p.hitbox);
            a.speed = 40;
            a.cooldown = 140;
            a.origin = {GlobalConstants::tileSize/2, GlobalConstants::tileSize/2};
            a.aimed = false;
            for(int i = -1; i < 2; ++i){
                for(int j = -1; j < 2;++j){
                    if (i == 0 && j == 0){
                        continue;
                    }
                    p.velocity = {(double)i, (double)j};
                    a.addProjectile(p);
                }
            }
            break;
        default:
            break;
    }

}
template <class T>
void AbilityPicker<T>::bossMelee(int i, T& a){

}
template <class T>
void AbilityPicker<T>::pickAbility(T& a, int i, AbilitySet set){
    T clean;
    a = clean;//clearing any old stuff set
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

template class AbilityPicker<Ability>;
template class AbilityPicker<TelegraphedAbility>;
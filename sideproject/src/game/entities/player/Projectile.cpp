//
// Created by bnorb on 31.12.19.
//

#include "Projectile.hpp"
#include "../../GlobalObjects.h"

Projectile::Projectile(vec_t positionTmp, int angle)
    : angle(angle)
    , status()
{
    position = positionTmp;
}

void Projectile::upkeep(double delta) {
    if(alive) {
        move(delta);
        timeToLive -= delta;
        vec_t vMax = utility::getMax(hitbox);
        vec_t vMin = utility::getMin(hitbox);
        vMax += position;
        vMin += position;
        if(vMax.x >= GlobalObjects::resolution.first || vMax.y >= GlobalObjects::resolution.second || vMin.x <= 0 || vMin.y <= 0){
            alive = false;
        }
        if (timeToLive < 0) {
            alive = false;
        }
    }

}

void Projectile::resolve(Player& p){
    if(alive) {
        for(auto& s : status) {
            switch (s.type) {
                case BLEED:
                    if(!p.vit.bleeding) {
                        p.vit.bleed += s.intensity;
                    }
                    break;
                case SHOCK:
                    if(!p.vit.shocked) {
                        p.vit.shock += s.intensity;
                    }
                    break;
                case BURN:
                    if(!p.vit.burning) {
                        p.vit.burn += s.intensity;
                    }
                    break;
                case ROT:
                    if(!p.vit.rotting) {
                        p.vit.rot += s.intensity;
                    }
                    break;
                case FRENZY:
                    if(!p.vit.frenzied) {
                        p.vit.frenzy += s.intensity;
                    }
                    break;
                default:
                    break;
            }
        }
        p.getHit(damage);
        alive = false; //piercing prjectiles?
    }
}

bool Projectile::collide(Movable& m){//this could be in movable...
    if(!m.iframes && utility::hitboxCollision(hitbox, position, m.hitbox, m.position)){
        return true;
    }
    return false;
}
bool Projectile::collide(Movable& m, bool weirdjank){//this could be in movable...
    if(!m.iframes && utility::hitboxCollision(hitbox, position, m.hitbox, m.position)){
        return true;
    }
    return false;
}
void Projectile::baseInit() {

}
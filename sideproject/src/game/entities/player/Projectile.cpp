//
// Created by bnorb on 31.12.19.
//

#include "Projectile.hpp"

Projectile::Projectile(vec_t positionTmp, int angle)
    : angle(angle)
    , status()
{
    position = positionTmp;
}

void Projectile::upkeep(double delta) {
    if(alive) {
        angle %= 360;
        move(delta);
        timeToLive -= delta;
        if (timeToLive < 0) {
            alive = false;
        }
    }

}

void Projectile::resolve(Player& p){
    if(alive) {
        p.getHit(damage);
        alive = false; //piercing prjectiles?
    }
}

bool Projectile::collide(Movable m){//this could be in movable...
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
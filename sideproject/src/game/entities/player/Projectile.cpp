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
    angle %= 360;
    move(delta, nullptr);

    // dummy
    /*
     * if (collision) {
     *   performActions();
     *   deleteProjectile();
     * }
     */

}

void Projectile::resolve(Player p){
    if(alive) {
        p.getHit(damage);
        alive = false; //piercing prjectiles?
    }
}

bool Projectile::collide(Movable m){//this could be in movable...
    //dumbo iteration TODO: aabbs
    for(auto& tri_proj : hitbox){
        for(auto& tri_mov : m.hitbox){
            if(!m.iframes && utility::triangleTriangleIntersection(tri_proj, position, tri_mov, m.position)){
                return true;
            }
        }
    }
    return false;
}

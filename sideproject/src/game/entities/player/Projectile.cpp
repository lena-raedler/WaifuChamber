//
// Created by bnorb on 31.12.19.
//

#include "Projectile.hpp"

Projectile::Projectile()
    : angle(0),
      velocity(10),
      alive(true) {}

Projectile::~Projectile() {}

void Projectile::upkeep(int delta) {
    angle %= 360;
    move(delta);

    // dummy
    /*
     * if (collision) {
     *   performActions();
     *   deleteProjectile();
     * }
     */

}

void Projectile::resolve(Player p){
    p.getHit(damage);


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
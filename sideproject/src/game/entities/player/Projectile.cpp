//
// Created by bnorb on 31.12.19.
//

#include "Projectile.hpp"

Projectile::Projectile()
    : position(Vec2<int> {0, 0}),
      angle(0),
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
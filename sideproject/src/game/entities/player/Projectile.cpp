//
// Created by bnorb on 31.12.19.
//

#include "Projectile.hpp"

Projectile::Projectile() :
 position(Vec2<int> {0, 0}),
 direction(Vec2<int> {1, 0}),
 velocity(10) {}

Projectile::~Projectile() {}
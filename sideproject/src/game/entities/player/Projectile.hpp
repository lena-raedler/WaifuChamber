//
// Created by bnorb on 31.12.19.
//

#pragma once

#include "../../utils/Vec2.h"

class Projectile {
public:
    Projectile();
    ~Projectile();

private:
    Vec2<int> position;
    Vec2<int> direction;
    int velocity;
};


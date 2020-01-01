//
// Created by bnorb on 31.12.19.
//

#pragma once

#include "../../utils/Vec2.h"
#include "Movable.h"

class Projectile : public Movable {
public:
    Projectile();
    ~Projectile();

private:
    // Current position of the projectile as a 2d point
    Vec2<int> position;

    // Direction in which the projectile flies
    // 0 = Right, 90 = upwards etc.
    // value between 0 and 359
    int angle;

    // How many pixels the projectile moves per loop
    int velocity;

    // Check in game.cpp if the projectile should be deleted
    bool alive = true;

    void upkeep(int delta);
};


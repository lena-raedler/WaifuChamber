//
// Created by bnorb on 31.12.19.
//

#pragma once

#include "../../utils/Vec2.h"
#include "../../utils/utility.h"
#include "Movable.h"
#include "player.h"
#include "statuseffect.h"
#include <vector>
#include "../../utils/ImageNew.hpp"


enum projectile_owner{PLAYER, HOSTILE};

//template <typename HOSTILE = true> maybe later
class Projectile : public Movable {
public:
    Projectile() = default;
    Projectile(vec_t position, int angle);
    //FUCK PRIVACY
    // Current position of the projectile as a 2d point
    //Vec2<int> position; not needed, inherit from movable, also do you want stuttering projectiles? because that is how you get stuttering projectiles!

    // Direction in which the projectile flies
    // 0 = Right, 90 = upwards etc.
    // value between 0 and 359
    int angle;

    // How many pixels the projectile moves per loop
    //int velocity;

    double damage= 20;//TODO remove this default val

    statuseffect status;

    //who is owning the projectile? default to enemy for testing
    projectile_owner owner = HOSTILE;

    // Check in game.cpp if the projectile should be deleted
    bool alive = true;

    void upkeep(double delta);
    void resolve(Player p); //this will be called on the object the projectile collides with
    bool collide(Movable m);
    ImageNew imageNew;
};


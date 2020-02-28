//
// Created by auki on 28.02.20.
//

#include "LockedWall.h"
#include "Message.hpp"

void LockedWall::init(){
    pos_double = {static_cast<double>(position.first), static_cast<double>(position.second)};
    int offs = orientation ? GlobalConstants::tileSize : -GlobalConstants::tileSize;
    utility::fillDefaultHitbox(hitboxOpen, 1, 1, {static_cast<double>(offs), 0});
    utility::fillDefaultHitbox(hitbox);
}

void LockedWall::unlock(vec_t pos){
    utility::encode(GlobalObjects::savedVariables.oneways, id);
    closed = false;
    utility::displayMessage("Unlocked!", pos, 100, 1234);
}
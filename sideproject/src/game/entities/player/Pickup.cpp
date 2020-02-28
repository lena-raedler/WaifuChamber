//
// Created by auki on 27.02.20.
//

#include "Pickup.hpp"

void Pickup::setFunction() {
    switch(id){
        case 0:
            pFunction = &PickupFunctions::dungeonBossKey;
            break;
        default:
            break;
    }
}
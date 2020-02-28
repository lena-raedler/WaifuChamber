//
// Created by auki on 28.02.20.
//

#include "PickupFunctions.hpp"

namespace PickupFunctions {
    void test(){
        GlobalObjects::playerPtr->addKey(2);
    }

    void dungeonBossKey(){
        GlobalObjects::playerPtr->addKey(1);
    }

};
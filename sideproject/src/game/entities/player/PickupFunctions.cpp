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

    void forestKey(){
        GlobalObjects::playerPtr->addKey(3);
    }
    void towerKey1(){
        GlobalObjects::playerPtr->addKey(4);
    }
    void towerKey2(){
        GlobalObjects::playerPtr->addKey(4);
    }

};
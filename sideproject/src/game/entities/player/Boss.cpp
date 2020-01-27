//
// Created by auki on 27.01.20.
//

#include "Boss.h"
void Boss::addHealthBar(int i){
    healthbars.push_back(std::make_pair(i, i));
}
void Boss::upkeep(double d){
    if(healthbars.size() > 0) {
        if (healthbars[0].first < 1){
            healthbars.erase(healthbars.begin());
        }
    } else{
        defeated = true;
        return;
    }

    vec_t playerPos = GlobalObjects::playerPtr->position;
    velocity.x = playerPos.x - position.x;
    velocity.normalize();
    velocity*=speed;
    move(d);
}
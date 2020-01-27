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
    velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
    velocity.x *=speed;
    for(auto& stuff : abilities){
        Ability& a= std::get<0>(stuff);
        [[maybe_unused]] double& d= std::get<1>(stuff);
        [[maybe_unused]] int& p= std::get<2>(stuff);

        if(a.isAvail()){//todo stuff
            a.use(position);
        }
    }
    move(d);
}
void Boss::getHit(double d){
    if(healthbars.size() > 0){
        healthbars[0].first -= d;
        std::cout << healthbars[0].first << std::endl;
    }
}
void Boss::addAbility(Ability a, double probability, int phase){
    abilities.push_back({a, probability, phase});
}
void Boss::kill(){
    //dostuff
}
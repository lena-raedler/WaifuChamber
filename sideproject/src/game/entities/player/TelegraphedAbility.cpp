//
// Created by auki on 11.02.20.
//

#include "TelegraphedAbility.h"
void TelegraphedAbility::useIfAvail(double delta, vec_t& pos){
    if(isAvail(delta)){
        use(pos);
        soundUse.play();
    }
}
bool TelegraphedAbility::isAvail(double delta) {
    if (lastUsed < 0){
        lastUsed = cooldown;

        return true;
    }
    return false;
}

void TelegraphedAbility::use(vec_t pos) {
    pos = pos + origin;

    vec_t tmp;

    for(auto& ta : attack){
        ta.spawn();
    }
}
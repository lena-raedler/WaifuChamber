//
// Created by auki on 10.01.20.
//

#ifndef WAIFU_STATUSEFFECT_H
#define WAIFU_STATUSEFFECT_H

enum status{BLEED, SHOCK, BURN, ROT, FRENZY};//this is gonna get templated so hard
/*
 * Bleed = dot + -50% stam regen
 * shock = slow
 * burn = dot + 50% healing reduction
 * rot = something so vile i have to think about how im going to fuck the player (instant death???, no stamina regen?, mana drain?)
 * frenzy = +50% damage taken, +20% damage dealt
 */
class statuseffect {//TODO
    status type;
    int intensity;
    double duration;

    void process();

};


#endif //WAIFU_STATUSEFFECT_H

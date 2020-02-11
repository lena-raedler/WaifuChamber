//
// Created by auki on 10.01.20.
//

#ifndef WAIFU_STATUSEFFECT_H
#define WAIFU_STATUSEFFECT_H

enum status{BLEED, SHOCK, BURN, ROT, FRENZY};//this is gonna get templated so hard  // Give me the templates, daddy-o
/*
 * Bleed = dot + -50% stam regen
 * shock = slow
 * burn = dot + 50% healing reduction
 * rot = something so vile i have to think about how im going to fuck the player (instant death???, no stamina regen?, mana drain?)
 * frenzy = +50% damage taken, +20% damage dealt
 */
struct statuseffect {//TODO
    status type;
    int intensity;
    double duration = 100;
    double durationLeft = duration;

};


#endif //WAIFU_STATUSEFFECT_H

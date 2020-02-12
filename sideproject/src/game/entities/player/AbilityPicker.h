//
// Created by auki on 09.02.20.
//

#ifndef WAIFU_ABILITYPICKER_H
#define WAIFU_ABILITYPICKER_H


#include "Ability.h"
enum AbilitySet{
    PL_RANGED,
    PL_MELEE,
    NPC_RANGED,
    NPC_MELEE,
    BOSS_RANGED,
    BOSS_MELEE
};
template<class T>
class AbilityPicker{
public:

    void plRanged(int i, T& a);
    void plMelee(int i, T& a);
    void npcRanged(int i, T& a);
    void npcMelee(int i, T& a);
    void bossRanged(int i, T& a);
    void bossMelee(int i, T& a);
    void pickAbility(T& a, int i, AbilitySet set);

};


#endif //WAIFU_ABILITYPICKER_H

//
// Created by auki on 27.01.20.
//

#ifndef WAIFU_BOSS_H
#define WAIFU_BOSS_H
#include "Movable.h"
#include "Ability.h"

class Boss : public Movable {
public:
    std::vector<std::pair<int, int>> healthbars;//cur, max
    //virtual void specialStuff(double d);
    int phase = 1;
    int id;
    std::vector<std::tuple<Ability, double, int>> abilities;

    bool defeated = false;
    double speed;
    std::string name;

    void addHealthBar(int i);
    void upkeep(double d);

    void getHit(double d);
    void kill();

    void addAbility(Ability a, double probability, int phase);


};


#endif //WAIFU_BOSS_H
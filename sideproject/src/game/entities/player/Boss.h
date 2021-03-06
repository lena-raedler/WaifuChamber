//
// Created by auki on 27.01.20.
//

#ifndef WAIFU_BOSS_H
#define WAIFU_BOSS_H
#include "Movable.h"
#include "Ability.h"
#include "Bar.hpp"
#include "EnemyBuilder.h"
#include "BossBuilder.h"
#include "TelegraphedAbility.h"
#include "../../utils/Rgba.h"
#include "../../utils/Text.hpp"
#include "Sprites.h"

class Boss : public Movable {
public:
    std::vector<std::pair<int, int>> healthbars;//cur, max
    //std::vector<Bar> bars;
    //Bar* healthBar = Bar();
    //std::unique_ptr<Bar> healthBar;
    Bar healthBar;
    std::vector<Bar> bars;
    int souls = 2000;

    //virtual void specialStuff(double d);
    int phase = 1;
    int id;
    std::vector<std::tuple<Ability, double, int>> abilities;
    std::vector<std::tuple<TelegraphedAbility, double, int>> telegraphedAbilities;

    bool defeated = false;
    double speed;
    std::string name;
    Text nameText;

    void (*phaseTransitionAbility)(int a, Boss& b);

    void addHealthBar(int i, Rgba borderColor, Rgba barColor);
    void upkeep(double d);

    void getHit(double d);
    void kill();

    void addAbility(Ability a, double probability, int phase);
    void transitionPhase();
    void addAbility(TelegraphedAbility a, double probability, int phase);
    // double healthPercentage(){return (double) hp / maxHp;}

    // for sprite purposes
    Sprites bossSprite;
    void render(Renderer& renderer);
    void init(Renderer& renderer);

};


#endif //WAIFU_BOSS_H

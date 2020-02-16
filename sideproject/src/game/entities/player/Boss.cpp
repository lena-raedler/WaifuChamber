//
// Created by auki on 27.01.20.
//
#include "../../SavedVariables.h"
#include "Boss.h"
void Boss::addHealthBar(int i, Rgba borderColor, Rgba barColor){
    healthbars.push_back(std::make_pair(i, i));
    //bars.push_back({64, 900, 1500, 30, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}});

    //int x = 64;
    //int y = 900;
    int x = 64;
    int y = GlobalObjects::resolution.second - 20;
    int width = GlobalObjects::resolution.first - 128;
    int height = 16;
    healthBar.x = x;
    healthBar.y = y;
    healthBar.width = width;
    healthBar.height = height;
    //healthBar = {x, y, width, height, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}};
    healthBar.borderRect = {x, y, width, height};
    healthBar.backgroundRect = {x + 5, y + 5, width - 10, height - 10};
    healthBar.barRect = {x + 5, y + 5, width - 10, height - 10};
    //healthBar.borderColor = {0xFF, 0x80, 0x80, 0xFF};
    //healthBar.barColor = {0xFF, 0x00, 0x00, 0xFF};
    healthBar.borderColor = borderColor;
    healthBar.barColor = barColor;

    bars.push_back(healthBar);

    //healthBar->x = 64;
    /*
    healthBar->y = 900;
    healthBar->width = 1500;
    healthBar->height = 30;
    healthBar->borderColor = {0xFF, 0x80, 0x80, 0xFF};
    healthBar->barColor = {0xFF, 0x00, 0x00, 0xFF};
     */
    //*healthBar({64, 900, 1500, 30, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}});
}
void Boss::upkeep(double d){
    if(healthbars.size() > 0) {
        if (healthbars[0].first < 1){
            healthbars.erase(healthbars.begin());
            bars.erase(bars.begin());
            transitionPhase();
        }
    } else{
        BossBuilder::bossDefeated(id);
        defeated = true;
        kill();
        return;
    }

    // Bn0rb start
    for (size_t i = 0; i < healthbars.size(); i++) {
        bars[i].updateBar(static_cast<double>(healthbars[i].first) / healthbars[i].second);
    }
    healthBar.updateBar(static_cast<double>(healthbars[0].first) / healthbars[0].second);
    // Bn0rb end

    vec_t playerPos = GlobalObjects::playerPtr->position;
    velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
    velocity.x *=speed;
    for(auto& stuff : abilities){
        Ability& a= std::get<0>(stuff);
        [[maybe_unused]] double& d= std::get<1>(stuff);
        int& p= std::get<2>(stuff);

        if(p <= phase){
            a.useIfAvail(d, position);
            a.lastUsed -= d;
        }
    }
    for(auto& stuff : telegraphedAbilities){
        TelegraphedAbility& a= std::get<0>(stuff);
        [[maybe_unused]] double& d= std::get<1>(stuff);
        int& p= std::get<2>(stuff);

        if(p <= phase){
            a.useIfAvail(d, position);
            a.lastUsed -= d;
        }
    }
    move(d);
}
void Boss::getHit(double d){
    if(healthbars.size() > 0){
        healthbars[0].first -= d;
    }
}
void Boss::addAbility(Ability a, double probability, int phase){
    abilities.push_back({a, probability, phase});
}
void Boss::addAbility(TelegraphedAbility a, double probability, int phase){
    telegraphedAbilities.push_back({a, probability, phase});
}
void Boss::kill(){
    GlobalObjects::enemies.clear();
    GlobalObjects::savedVariables.bossesDefeated |= (1 << (id - 1));
    std::ofstream file("savegame.txt", std::ios::trunc);
    if (file.good()) {
        GlobalObjects::savedVariables.serialize(file);
    }
    file.close();
    //dostuff
}
void Boss::transitionPhase() {
    (this->phaseTransitionAbility)(++phase, *this);
}
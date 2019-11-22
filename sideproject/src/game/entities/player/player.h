//
// Created by lena on 11/11/19.
//

#ifndef WAIFUCHAMBER_PLAYER_H
#define WAIFUCHAMBER_PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "../../utils/renderer.h"
#include "../../utils/Vec2.h"
#include <utility>
#include "Movable.h"

struct attributes{
    int str;
    int dex;
    int agi;
    int bluedex;// (intelligence)
    int con;
};
class Player : public Movable {
public:
    Player();
    ~Player();

    void updatePlayerPosition(double x, double y);
    int jumps;
    void jump();

    //std::vector<statuseffect> statusEffects; TODO: implement status effects






};


#endif //WAIFUCHAMBER_PLAYER_H

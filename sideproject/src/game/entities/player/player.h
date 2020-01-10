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
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include "statuseffect.h"

struct attributes{
    int str;
    int dex;
    int agi;
    int bluedex;// (intelligence)
    int con;
};
struct vitals{
    int maxHp = 100;
    int hp = 50;
    double healthPercentage = (double) hp / maxHp;
    int maxStam = 100;
    int stam = 50;
    int maxMp = 100;
    int mp = 50;
};
class Player : public Movable {
public:
    Player();
    ~Player();

    const int iframeduration = 500;
    void updatePlayer(double x, double y);
    int jumps = 2;
    const int jumpCooldown = 250; //ms
    const double jumpSpeed = -30;
    std::chrono::high_resolution_clock::time_point lastJump = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point lastHit;
    attributes attr;
    vitals vit;

    void jump();
    bool canJump();
    void upkeep(double delta);//call this every frame
    void getHit(double damage);
    void getHit(double damage, statuseffect status);

    void processStatuseffects(statuseffect status);

    void rest();

    //std::vector<statuseffect> statusEffects; TODO: implement status effects






};


#endif //WAIFUCHAMBER_PLAYER_H

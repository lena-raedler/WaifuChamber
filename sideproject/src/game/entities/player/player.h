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


class Player {
public:
    Player();
    ~Player();
    void render(Renderer& renderer);
    std::string getTextureLocation();
    Vec2<double> position;
    void updatePlayerPosition(double x, double y);
    int jumps;
    void jump();
    void moveLeft();
    void moveRight();
    //std::vector<statuseffect> statusEffects; TODO: implement status effects



private:
    std::string textureLocation;


};


#endif //WAIFUCHAMBER_PLAYER_H

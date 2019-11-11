//
// Created by lena on 11/11/19.
//

#ifndef WAIFUCHAMBER_PLAYER_H
#define WAIFUCHAMBER_PLAYER_H

#include <iostream>
#include <string>
#include "../../utils/renderer.h"
#include <utility>


class Player {
public:
    Player();
    ~Player();
    void render(Renderer& renderer);
    std::string getTextureLocation();
    std::pair<int, int> getPlayerPosition();
    void updatePlayerPosition(int x, int y);



private:
    std::string textureLocation;
    int x_position;
    int y_position;


};


#endif //WAIFUCHAMBER_PLAYER_H

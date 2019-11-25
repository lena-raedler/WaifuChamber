//
// Created by lena on 11/11/19.
//

#include "player.h"
#include "../../utils/renderer.h"
#include <iostream>
#include <string>
#include <utility>

Player::Player() {
    position.x = 50;
    position.y = 50;
    textureLocation = "files/textures/test_player.png";
}

Player::~Player() {

}



void Player::updatePlayerPosition(double x, double y) {
    position.x = x;
    position.y = y;
}

void Player::upkeep(double delta){
    move(delta);
    if (position.y < 51){
        jumps = 2;
    }
}
void Player::jump(){
    jumps--;
    //do other stuff related to jumoing (moving is currently done in game change that jank shit later)
}
bool Player::canJump(){
    std::cout << "YOU FOOL" << std::endl;
    if(jumps > 0 && true /*TODO CD on jump*/){
        return true;
    }
    return false;
}

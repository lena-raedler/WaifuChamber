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

const void Player::render(Renderer &renderer) {
    //do something
}

const std::string Player::getTextureLocation() {
    return textureLocation;
}

void Player::updatePlayerPosition(double x, double y) {
    position.x = x;
    position.y = y;
}

void Player::move(double delta){
    position += velocity * delta;
}

//
// Created by lena on 11/11/19.
//

#include "player.h"
#include "../../utils/renderer.h"
#include <iostream>
#include <string>
#include <utility>

Player::Player() {
    x_position = 50;
    y_position = 50;
    textureLocation = "files/textures/test_player.png";
}

Player::~Player() {

}

void Player::render(Renderer &renderer) {
    //do something
}

std::string Player::getTextureLocation() {
    return textureLocation;
}

std::pair<int, int> Player::getPlayerPosition() {
    auto position = std::make_pair(x_position, y_position);
    return position;
}

void Player::updatePlayerPosition(int x, int y) {
    x_position = x;
    y_position = y;
}

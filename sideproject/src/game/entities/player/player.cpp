//
// Created by lena on 11/11/19.
//

#include "player.h"


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
    if (position.y > 199 && velocity.y >= 0){
        if (jumps != 2) {
            std::cout << "Jumps reset!" << std::endl;
        }
        jumps = 2;

        isFalling = false;
    } else{
        isFalling = true;
    }
}
void Player::jump(){
    jumps--;
    std::cout << "Jumping, Jumps left: " << jumps << std::endl;
    if(velocity.y > 0){
        velocity.y = jumpSpeed;
    } else{
        velocity.y += jumpSpeed;
    }
    lastJump = std::chrono::high_resolution_clock::now();
    //do other stuff related to jumoing (moving is currently done in game change that jank shit later)
}
bool Player::canJump(){

    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastJump = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastJump);
    //std::chrono::duration<double, std::milli> fp_ms = time - lastJump;

    if(jumps > 0 && (timeSinceLastJump > std::chrono::milliseconds(jumpCooldown)) /**/){
        return true;
    }
    return false;
}

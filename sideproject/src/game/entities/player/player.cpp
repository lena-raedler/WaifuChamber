//
// Created by lena on 11/11/19.
//

#include "player.h"


Player::Player() {
    position.x = 50;
    position.y = 50;
    textureLocation = "files/textures/test_player.png";
    usesPlatforms = true;
}

Player::~Player() {

}



void Player::updatePlayer(double x, double y) {
    position.x = x;
    position.y = y;

}

void Player::upkeep(double delta){


    move(delta);
    if (velocity.y <= 0 + GlobalConstants::epsilon){

        isFalling = true;//todo fix
    } else{
        isFalling = true;
    }
    if(iframes){//mercy frames
        auto time = std::chrono::high_resolution_clock::now();
        auto timeSinceLastHit = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastHit);
        if(timeSinceLastHit >  std::chrono::milliseconds(iFrameDuration)){
            iframes = false;
        }
    }
}
void Player::jump(){
    jumps--;
    std::cout << "Jumping, Jumps left: " << jumps << std::endl;
    /*
    if(velocity.y > 0){
        velocity.y = jumpSpeed;
    } else{
        velocity.y += jumpSpeed;
    } */ //momentum code

    velocity.y = jumpSpeed; //clamp to something for increased momentum?
    lastJump = std::chrono::high_resolution_clock::now();
    //do other stuff related to jumoing (moving is currently done in game change that jank shit later)
}
bool Player::canJump(){

    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastJump = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastJump);
    //std::chrono::duration<double, std::milli> fp_ms = time - lastJump;

    return jumps > 0 && (timeSinceLastJump > std::chrono::milliseconds(jumpCooldown));
}
void Player::pause() {
    lastPause = std::chrono::high_resolution_clock::now();
}
bool Player::canPause() {
    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastPause = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastPause);
    return timeSinceLastPause > std::chrono::milliseconds(pauseCooldown);
}
void Player::spawnProjectile() {    // Not good, currently used so that there is a slight delay until a new projectile can be spawned.
    lastSpawnProjectile = std::chrono::high_resolution_clock::now();
}
bool Player::canSpawnProjectile() {
    auto time = std::chrono::high_resolution_clock::now();
    auto timeSinceLastSpawnProjectile = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastSpawnProjectile);
    return timeSinceLastSpawnProjectile > std::chrono::milliseconds(spawnProjectileCooldown);
}
void Player::getHit(double damage) {
    iframes = true;
    lastHit = std::chrono::high_resolution_clock::now();
    vit.hp -= damage;
}
void Player::getHit(double damage, statuseffect status){
    getHit(damage);
    //processStatuseffect(status);
}

void Player::rest(){
    //respawn enemies
    vit.hp = vit.maxHp;
    vit.mp = vit.maxMp;
}
void Player::kill(){
    position = lastCP->position;
    rest();
}
void Player::grounded(){
    jumps = 2;
}

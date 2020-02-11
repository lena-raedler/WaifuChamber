//
// Created by lena on 11/11/19.
//

#include "player.h"
#include "../../GlobalObjects.h"
//#include "../../utils/Rgba.hpp"


Player::Player()
    //: healthBar({64, 64, 210, 30, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}})
{
    int x = 64;
    int y = 64;
    int width = 210;
    int height = 30;
    healthBar.x = x;
    healthBar.y = y;
    healthBar.width = width;
    healthBar.height = height;
    //healthBar = {x, y, width, height, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}};
    healthBar.borderRect = {x, y, width, height};
    healthBar.backgroundRect = {x + 5, y + 5, width - 10, height - 10};
    healthBar.barRect = {x + 5, y + 5, width - 10, height - 10};
    healthBar.borderColor = {0xFF, 0x80, 0x80, 0xFF};
    healthBar.barColor = {0xFF, 0x00, 0x00, 0xFF};

    // Stamina
    staminaBar.x = x + width + 5;
    staminaBar.y = healthBar.y;
    staminaBar.width = healthBar.width;
    staminaBar.height = healthBar.height;
    staminaBar.borderRect = {staminaBar.x, staminaBar.y, staminaBar.width, staminaBar.height};
    staminaBar.backgroundRect = {staminaBar.x + 5, staminaBar.y + 5, staminaBar.width - 10, staminaBar.height - 10};
    staminaBar.barRect = staminaBar.backgroundRect;
    staminaBar.borderColor = {0x8F, 0xC3, 0x1F, 0xFF};
    staminaBar.barColor = {0x00, 0x99, 0x44, 0xFF};

    // Bleed
    bleedBar.width = bleedBar.borderRect.w = GlobalConstants::tileSize*2;
    bleedBar.height = bleedBar.borderRect.h = 16;
    bleedBar.backgroundRect.w = bleedBar.barRect.w = bleedBar.width - 8;
    bleedBar.backgroundRect.h = bleedBar.barRect.h = bleedBar.height - 8;
    //bleedBar.borderColor = {0xFF, 0xFF, 0xFF, 0xFF};
    bleedBar.borderColor = GlobalConstants::WHITE;
    bleedBar.barColor = {0xFF, 0x00, 0x00, 0xFF};

    bleedActiveBar = bleedBar;
    bleedActiveBar.borderColor = GlobalConstants::YELLOW;
    bleedActive = false;

    // Player position
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

    velocity.x *= speedMultiplier;
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
    checkStatusEffects();
    std::vector<statuseffect> vecS;
    for(auto& s: statusEffects){
        processStatusEffects(s, delta);
        if(s.durationLeft > 0){
            vecS.push_back(s);
        } else{
            removeStatusEffect(s);
        }
    }
    statusEffects = vecS;

    for(auto& a: GlobalObjects::abilities){
        a.lastUsed -= delta;
    }

}
void Player::jump(){
    Mix_PlayChannel(-1, GlobalObjects::chunkPtr[1], 0);
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
    if(!iframes) {
        iframes = true;
        lastHit = std::chrono::high_resolution_clock::now();
        vit.hp -= damage;
    }
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
    Mix_PlayChannel(-1, GlobalObjects::chunkPtr[0], 0);
    position = lastCP->position;
    rest();
}
void Player::grounded(double delta) {
    if(velocity.y >= 0) {
        jumps = 2;
    }
    vit.stam += delta * vit.stamRegen * stamRegenMultiplier;
    vit.stam = std::min(vit.stam, vit.maxStam);
}

void Player::applyStatusEffect(statuseffect &status) {//BLEED, SHOCK, BURN, ROT, FRENZY
    switch(status.type){
        case BLEED:
            bleedActive = true;
            stamRegenMultiplier /= 10;
            break;
        case SHOCK:
            speedMultiplier /= 2;
            break;
        case BURN:
            break;
        case ROT:
            break;
        case FRENZY:
            break;
        default:
            break;
    }
    statusEffects.push_back(status);

}
void Player::processStatusEffects(statuseffect &status, double delta) {
    // int heightMultiplier = 1;    // Increase after a bar has updated
    if(status.durationLeft > 0) {
        switch (status.type) {
            case BLEED:
                vit.hp -= ((vit.maxHp * 0.3)/status.duration) * delta;

                bleedActiveBar.updateBar(status.durationLeft / status.duration);
                bleedActiveBar.borderRect.x = position.x - bleedActiveBar.width / 4;
                bleedActiveBar.borderRect.y = position.y - bleedActiveBar.height - 4;
                bleedActiveBar.backgroundRect.x = bleedActiveBar.barRect.x = bleedActiveBar.borderRect.x + 4;
                bleedActiveBar.backgroundRect.y = bleedActiveBar.barRect.y = bleedActiveBar.borderRect.y + 4;
                break;
            case SHOCK:
                break;
            case BURN:
                break;
            case ROT:
                break;
            case FRENZY:
                break;
            default:
                break;
        }
        status.durationLeft -= delta;
    }

}
void Player::removeStatusEffect(statuseffect &status) {
    switch(status.type){
        case BLEED:
            bleedActive = false;
            stamRegenMultiplier *= 10;
            vit.bleed = 0;
            break;
        case SHOCK:
            speedMultiplier *= 2;
            vit.shock = 0;
            break;
        case BURN:
            break;
        case ROT:
            break;
        case FRENZY:
            break;
        default:
            break;
    }

}

void Player::checkStatusEffects(){
    if(vit.bleed >= vit.bleedRes){
        statuseffect s;
        s.type = BLEED;
        vit.bleed = -9999;
        applyStatusEffect(s);
    }
    if(vit.shock >= vit.shockRes){
        statuseffect s;
        s.type = SHOCK;
        vit.shock = -9999;
        applyStatusEffect(s);
    }
    if(vit.burn >= vit.burnRes){
        statuseffect s;
        s.type = BURN;
        vit.burn = -9999;
        applyStatusEffect(s);
    }
    if(vit.rot >= vit.rotRes){
        statuseffect s;
        s.type = ROT;
        vit.rot = -9999;
        applyStatusEffect(s);
    }
    if(vit.frenzy >= vit.frenzyRes){
        statuseffect s;
        s.type = FRENZY;
        vit.frenzy = -9999;
        applyStatusEffect(s);
    }
}

void Player::updateStatusEffectBars() {
    /*for (statuseffect effect : statusEffects) {
        switch (effect.type) {
            case BLEED:

                break;
            default:
                break;
        }
    }*/

    // TODO make more efficient
    bleedBar.borderRect.x = position.x - bleedBar.width / 4;
    bleedBar.borderRect.y = position.y - bleedBar.height - 4;   // TODO Make consistent with multiple status bars
    bleedBar.backgroundRect.x = bleedBar.barRect.x = bleedBar.borderRect.x + 4;
    bleedBar.backgroundRect.y = bleedBar.barRect.y = bleedBar.borderRect.y + 4;

    //bleedActiveBar = bleedBar;

    bleedActiveBar.borderColor = GlobalConstants::YELLOW;
}
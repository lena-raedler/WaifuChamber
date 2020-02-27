//
// Created by lena on 11/11/19.
//

#include "player.h"
#include "../../GlobalObjects.h"
#include "../../utils/Text.hpp"
#include "../../utils/LingeringText.hpp"
//#include "../../utils/Rgba.hpp"


Player::Player()
    //: healthBar({64, 64, 210, 30, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}})
{
    int x = 64;
    int y = 64;
    int width = 210;
    int height = 30;

    //int x = 64 + 84/4;
    //int y = 64 + 22/2;
    //int width = (824 - 84 - 83)/4;
    //int height = (82 - 23 - 22)/2;

    healthBar.x = x;
    healthBar.y = y;
    healthBar.width = width;
    healthBar.height = height;
    healthBar = {x, y, width, height, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}};
    healthBar.borderRect = {x, y, width, height};
    healthBar.backgroundRect = {x + 5, y + 5, width - 10, height - 10};
    //healthBar.backgroundRect = {x, y, width, height};
    healthBar.barRect = {x + 5, y + 5, width - 10, height - 10};
    //healthBar.barRect = {x, y, width, height};
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
    bleedBar.width = bleedBar.borderRect.w = statusBarWidth;
    bleedBar.height = bleedBar.borderRect.h = statusBarHeight;
    bleedBar.backgroundRect.w = bleedBar.barRect.w = bleedBar.width - statusBarBackgroundOffset;
    bleedBar.backgroundRect.h = bleedBar.barRect.h = bleedBar.height - statusBarBackgroundOffset;
    bleedBar.borderColor = GlobalConstants::WHITE;
    bleedBar.barColor = {0xFF, 0x00, 0x00, 0xFF};

    activeBleedBar = bleedBar;
    activeBleedBar.borderColor = GlobalConstants::YELLOW;

    // Shock
    shockBar = bleedBar;
    shockBar.barColor = GlobalConstants::BLUE;
    activeShockBar = shockBar;
    activeShockBar.borderColor = GlobalConstants::YELLOW;

    // Burn
    burnBar = bleedBar;
    burnBar.barColor = GlobalConstants::ORANGE;
    activeBurnBar = burnBar;
    activeBurnBar.borderColor = GlobalConstants::ORANGE;

    // Rot
    rotBar = bleedBar;
    rotBar.barColor = GlobalConstants::BROWN;
    activeRotBar = rotBar;
    activeRotBar.borderColor = GlobalConstants::BROWN;

    // Frenzy   // TODO Give a different color
    frenzyBar = bleedBar;
    frenzyBar.barColor = GlobalConstants::ORANGE;
    activeFrenzyBar = frenzyBar;
    activeFrenzyBar.borderColor = GlobalConstants::ORANGE;

    // Player position
    position.x = 50;
    position.y = 50;
    textureLocation = "files/textures/edgy_player.png";
    usesPlatforms = true;
}

Player::~Player() {

}



void Player::updatePlayer(double x, double y) {
    position.x = x;
    position.y = y;

}

void Player::upkeep(double delta){
    if(dashingUp){
        velocity = (dashDest - dashOrigin) * dashSpeed;
        dashDuration -= delta;
        if(dashDuration < 0){
            dashingUp = false;
            terminalVelocity={30, 50};
            gravityType = NORMAL;
            dashDuration = dashFullDuration;
            velocity *= 0.5;
            if(velocity.y < -15){
                velocity.y = -15;
            }
            iframes = false;
        }
    }
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
    vit.bleed -= delta * vit.statusDecay;
    vit.shock -= delta * vit.statusDecay;
    vit.burn -= delta * vit.statusDecay;
    vit.rot -= delta * vit.statusDecay;
    vit.frenzy -= delta * vit.statusDecay;

    vit.bleed = std::max(0.0, vit.bleed);
    vit.shock = std::max(0.0, vit.shock);
    vit.burn = std::max(0.0, vit.burn);
    vit.rot = std::max(0.0, vit.rot);
    vit.frenzy = std::max(0.0, vit.frenzy);


    for(auto& a: GlobalObjects::abilities){
        a.lastUsed -= delta;
    }

    // Update status bars
    healthBar.updateBar(vit.healthPercentage());
    staminaBar.updateBar(vit.staminaPercentage());
    bleedBar.updateBar(vit.bleedPercentage());
    shockBar.updateBar(vit.shockPercentage());
    burnBar.updateBar(vit.burnPercentage());
    rotBar.updateBar(vit.rotPercentage());
    updateStatusEffectBars();
    statusBarMultiplier = 1;    // Reset the offset multiplier (to stack bars ontop of each other)
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
    for(auto& s: statusEffects){
        removeStatusEffect(s);
    }
    vit.setStatusToZero();
    statusEffects.clear();
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
            vit.bleed = 0;
            vit.bleeding = true;
            stamRegenMultiplier /= 10;
            break;
        case SHOCK:
            vit.shock = 0;
            vit.shocked = true;
            terminalVelocity.x /= 2;
            break;
        case BURN:
            vit.burn = 0;
            vit.burning = true;
            break;
        case ROT:
            vit.rot = 0;
            vit.rotting = true;
            break;
        case FRENZY:
            vit.frenzy = 0;
            vit.frenzied = true;
            break;
        default:
            break;
    }
    statusEffects.push_back(status);

}
void Player::processStatusEffects(statuseffect &status, double delta) {
    if(status.durationLeft > 0) {
        switch (status.type) {
            case BLEED:
                vit.hp -= ((vit.maxHp * 0.3)/status.duration) * delta;
                setStatusBarPosition(activeBleedBar, status);
                break;
            case SHOCK:
                setStatusBarPosition(activeShockBar, status);
                break;
            case BURN:
                setStatusBarPosition(activeBurnBar, status);
                break;
            case ROT:
                setStatusBarPosition(activeRotBar, status);
                break;
            case FRENZY:
                vit.frenzy = 0;
                setStatusBarPosition(activeFrenzyBar, status);
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
            vit.bleeding = false;
            stamRegenMultiplier *= 10;
            vit.bleed = 0;
            break;
        case SHOCK:
            vit.shocked = false;
            terminalVelocity.x *= 2;
            vit.shock = 0;
            break;
        case BURN:
            vit.burning = false;
            vit.burn = 0;
            break;
        case ROT:
            vit.rotting = false;
            vit.rot = 0;
            break;
        case FRENZY:
            vit.frenzied = false;
            vit.frenzy = 0;
            break;
        default:
            break;
    }
}

void Player::checkStatusEffects(){
    if(vit.bleed >= vit.bleedRes){
        statuseffect s;
        s.type = BLEED;
        applyStatusEffect(s);
    }
    if(vit.shock >= vit.shockRes){
        statuseffect s;
        s.type = SHOCK;
        applyStatusEffect(s);
    }
    if(vit.burn >= vit.burnRes){
        statuseffect s;
        s.type = BURN;
        applyStatusEffect(s);
    }
    if(vit.rot >= vit.rotRes){
        statuseffect s;
        s.type = ROT;
        applyStatusEffect(s);
    }
    if(vit.frenzy >= vit.frenzyRes){
        statuseffect s;
        s.type = FRENZY;
        applyStatusEffect(s);
    }
}

void Player::updateStatusEffectBars() {
    if (vit.bleed > 0)
        setStatusBarPosition(bleedBar);
    if (vit.shock > 0)
        setStatusBarPosition(shockBar);
    if (vit.burn > 0)
        setStatusBarPosition(burnBar);
    if (vit.rot > 0)
        setStatusBarPosition(rotBar);
    if (vit.frenzy > 0)
        setStatusBarPosition(frenzyBar);
}

void Player::setStatusBarPosition(Bar& bar) {
    bar.borderRect.x = position.x - bar.width / 4;
    bar.borderRect.y = position.y - (bar.height+statusBarBackgroundOffset)*statusBarMultiplier++;
    bar.backgroundRect.x = bar.barRect.x = bar.borderRect.x + statusBarBackgroundOffset / 2;
    bar.backgroundRect.y = bar.barRect.y = bar.borderRect.y + statusBarBackgroundOffset / 2;
}
void Player::setStatusBarPosition(Bar& bar, statuseffect& status) {
    bar.updateBar(status.durationLeft / status.duration);
    setStatusBarPosition(bar);
}

vec_t Player::getMiddle(){
    return{position.x+GlobalConstants::tileSize/2, position.y + GlobalConstants::tileSize/2};
}

void Player::dashTo(vec_t dest){
    vit.stam -= dashStaminaCost;
    iframes = true;
    gravityType = NOGRAVITY;
    terminalVelocity = {100, 100};
    dashOrigin = getMiddle();
    dashDest = dest;
}
bool Player::areWeThereYet(vec_t dest){
    return (dest - position).length() <= GlobalConstants::epsilon;
}

bool Player::hasKey(Gate &g) {
    return (g.keyId == -1) || (1 & (GlobalObjects::savedVariables.keys >> g.keyId));
}

void Player::addKey(int keyId){
    std::string str ="Found key #" + std::to_string(keyId);
    LingeringText keyText;
    keyText.text.changeText(str);
    keyText.text.rect = {static_cast<int>(position.x - 50), static_cast<int>(position.y - 40)};
    keyText.text.changeFontSize(20);
    keyText.id = 1;
    keyText.duration = 100;
    keyText.print();
    GlobalObjects::savedVariables.keys |= (1 << keyId);
    GlobalObjects::savedVariables.serialize();
}

//functions for sprites - just leave me here
void Player::init(Renderer &renderer) {
    SDL_Surface* s = IMG_Load(textureLocation.c_str());
    texture = renderer.createTextureFromSurface(s);
    int textureWidth = s->w;
    int textureHeight = s->h;
    SDL_FreeSurface(s);
    playerSprite.spriteSheet = texture;
    int x_pos = 0;
    int y_pos = textureHeight/4;
    while((textureHeight - 2*(textureHeight/4)) >= y_pos ) {
        while((textureWidth - (textureWidth/3)) >= x_pos) {
            SDL_Rect r = {x_pos, y_pos, textureWidth/3, textureHeight/4};
            playerSprite.sprites.push_back(r);
            x_pos += textureWidth/3;
        }
        x_pos = 0;
        y_pos += textureHeight/4;
    }
    //add idle position
    SDL_Rect r = {textureWidth/3, 0, textureWidth/3, textureHeight/4};
    playerSprite.sprites.push_back(r);
}


void Player::render(Renderer &renderer) {
    Sprites toRender;
    toRender.spriteSheet = playerSprite.spriteSheet;
    if(isIdle) {
        toRender.sprites.push_back(playerSprite.sprites[6]);
    }
    else if(velocity.x < 0) {
        for(int i = 0; i < 3; i++) {
            toRender.sprites.push_back(playerSprite.sprites[i]);
        }
    }
    else {
        for(int i = 3; i < 6; i++) {
            toRender.sprites.push_back(playerSprite.sprites[i]);
        }
    }
    toRender.render(renderer, position);
}
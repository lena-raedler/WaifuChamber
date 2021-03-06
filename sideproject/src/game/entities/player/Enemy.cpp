//
// Created by auki on 26.01.20.
//

#include "Enemy.h"

void Enemy::upkeep(double delta){
    vec_t playerPos = GlobalObjects::playerPtr->position;
    switch(ai){
        case CHASE:
            velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
            velocity.x *=speed;
            break;
        case STATIONARY:
            velocity = {0, 0};
            break;
        case FLEE:
            velocity.x = std::clamp(position.x - playerPos.x, -1.0, 1.0);
            velocity.x *=speed;
            break;
        case PATROL:
            if(patrolPoints.size() > 0) {
                if (std::abs(position.x - patrolPoints[patrolCounter].x) < GlobalConstants::epsilon) {
                    if (!(++patrolCounter < patrolPoints.size())) {
                        patrolCounter = 0;
                    }
                }
                velocity.x = std::clamp(patrolPoints[patrolCounter].x - position.x, -1.0, 1.0);
                velocity.x *= speed;
            }
            break;
        case CONSTANT:
            break;
        case CHASEXY:
            velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
            velocity.y = std::clamp(playerPos.y - position.y, -1.0, 1.0);
            velocity.normalize();
            velocity *=speed;
            break;
        default:
            break;
    }
    move(delta);

    for(Ability& a : abilities){
        a.useIfAvail(delta, position);
        a.lastUsed -= delta;
    }
    for(auto& a: telegraphedAbilities){
        a.useIfAvail(delta, position);
        a.lastUsed -= delta;
    }

    healthBar.updateBar(healthPercentage());
    healthBar.x = position.x;
    healthBar.y = position.y - GlobalConstants::tileSize/2;
    healthBar.borderRect.x = healthBar.x;
    healthBar.borderRect.y = healthBar.y;
    healthBar.backgroundRect.x = healthBar.barRect.x = healthBar.x + healthBarOffset;
    healthBar.backgroundRect.y = healthBar.barRect.y = healthBar.y + healthBarOffset;
}
void Enemy::setMaxHealth(int i) {
    maxHealth = i;
    health = i;
}

void Enemy::getHit(double d){
    health -= d;
}

void Enemy::kill(){
    GlobalObjects::savedVariables.souls += souls;
    std::cout << "Souls: " << GlobalObjects::savedVariables.souls << std::endl;
    SDL_DestroyTexture(texture);
    //dostuff
}
void Enemy::chase(double d){
    vec_t playerPos = GlobalObjects::playerPtr->position;
    velocity.x = std::clamp(playerPos.x - position.x, -1.0, 1.0);
    velocity.x *=speed;

}
void Enemy::flee(double d){
    vec_t playerPos = GlobalObjects::playerPtr->position;
    velocity.x = std::clamp(position.x - playerPos.x, -1.0, 1.0);
    velocity.x *=speed;

}
void Enemy::init(Renderer &renderer) {
    if(hasSprite) {
        SDL_Surface *s = IMG_Load(textureLocation.c_str());
        texture = renderer.createTextureFromSurface(s);
        int textureWidth = s->w;
        SDL_FreeSurface(s);
        enemySprite.spriteSheet = texture;
        int x_pos = 0, y_pos = 0;
        while ((textureWidth - GlobalConstants::tileSize) >= x_pos) {
            SDL_Rect r = {x_pos, y_pos, GlobalConstants::tileSize, GlobalConstants::tileSize};
            enemySprite.sprites.push_back(r);
            x_pos += textureWidth / 4;

        }
    } else {
        SDL_Rect r = {(int)position.x, (int)position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        rec = std::make_shared<SDL_Rect>(r);
        SDL_Surface* s = IMG_Load(textureLocation.c_str());
        texture = renderer.createTextureFromSurface(s);
        SDL_FreeSurface(s);
    }
}

void Enemy::render(Renderer &renderer) {
    if(hasSprite) {
        enemySprite.render(renderer, position);
    } else {
        renderer.renderTexture(texture, nullptr, rec.get());
    }
    // Health bar
    if (health < maxHealth)
        healthBar.renderBar(renderer);
}
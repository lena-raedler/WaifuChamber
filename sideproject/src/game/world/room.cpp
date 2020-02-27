//
// Created by lena on 1/1/20.
//

#include "room.h"

Room::Room() {}

Room::Room(SDL_Texture *texture, SDL_Rect rectangle, std::unordered_map<SDL_Texture*, SDL_Rect> tileRectMap,
        std::vector<std::pair<int, int>> platformPositions, std::vector<std::pair<std::pair<int, int>, std::string>> gatePositions)
        : doorPositions(gatePositions) {
    backgroundtexture = texture;
    backgroundRectangle = rectangle;
    tileMap = tileRectMap;
    platformPositions = platformPositions;
}



void Room::render(Renderer &renderer) {
    renderer.renderTexture(backgroundtexture, nullptr, &backgroundRectangle);

    //for(auto it = tileMap.begin(); it != tileMap.end(); it++) {
    for(auto & it : tileMap) {
        renderer.renderTexture(it.first, nullptr, &(it.second));
    }

}
void Room::fillPlatformVector(std::vector<std::shared_ptr<Platform>>& p){
    p.clear();
    for(auto pair : platformPositions){
        p.push_back(std::make_shared<Platform>(pair, 0));
    }
    for(auto pair : wallPostitions) {
        p.push_back(std::make_shared<Platform>(pair, 1));
    }
    for(auto pair : ceilingPositions) {
        p.push_back(std::make_shared<Platform>(pair, 2));
    }
    for(auto pair : floorPositions) {
        p.push_back(std::make_shared<Platform>(pair, 3));
    }
}
void Room::fillDoorVector(std::vector<std::shared_ptr<Gate>>& g){
    g.clear();
    for(auto i : gates) {
        Gate gate;
        gate.position = {(double) i.position.first, (double) i.position.second};
        gate.nextRoomPath = i.path;
        gate.keyId = i.keyId;
        gate.leftLocked = i.leftLocked;
        gate.rightLocked = i.rightLocked;
        gate.newPosition = utility::convert(i.newPlayerPosition);
        utility::fillDefaultHitbox(gate.hitbox);
        g.push_back(std::make_shared<Gate>(gate));
    }

}
void Room::fillEnemyVector(std::vector<std::shared_ptr<Enemy>>& e){
    e.clear();
    for(auto& it: enemies) {
        EnemyBuilder::buildEnemy(e, it.id, it.position);
        auto eback = e.back();
        if(eback->ai == PATROL){
            if(it.patrolPoints.size() == 0){
                std::cout << "WARNING: Enemy with PATROL behaviour and no patrol points constructed." << std::endl;
            }
            for(auto& p : it.patrolPoints){
                eback->patrolPoints.push_back(utility::convert(p));
            }
        } else if(it.patrolPoints.size() > 0){
            std::cout << "WARNING: Enemy with patrol points with a non-PATROL behaviour constructed." << std::endl;
        }
    }
}

void Room::fillBossVector(std::vector<std::shared_ptr<Boss>>& b) {
    b.clear();
    for(auto& it: bossInformation) {
        BossBuilder::buildBoss(it.second, it.first);
    }
}

void Room::printP() {
    for(auto i : platformPositions) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Room::clear() {
    SDL_DestroyTexture(backgroundtexture);
    for(auto &i : tileMap) {
        SDL_DestroyTexture(i.first);
    }
    platformPositions.clear();
    wallPostitions.clear();
    ceilingPositions.clear();
    floorPositions.clear();
    doorPositions.clear();
    enemyInformation.clear();
}
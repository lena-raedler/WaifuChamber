//
// Created by lena on 1/1/20.
//

#pragma once

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "../utils/renderer.h"
#include <vector>
#include <sstream>
#include <unordered_map>
#include <utility>
#include "Gate.h"
#include "Platform.h"
#include "../entities/player/EnemyBuilder.h"
#include "../entities/player/BossBuilder.h"

enum TileType{
    BLANK,
    SOLID,
    EVENT,
    ENEMY
};
class RoomRep{//fancy vector containing the data for the room
    std::vector<TileType> vec;
    int dimSize;
    auto operator[](int i){
        return vec.begin() + i * dimSize;
    }
    void push_back(char c){

    }
};

class Room {
public:
    Room();
    Room(SDL_Texture* texture, SDL_Rect rectangle, std::unordered_map<SDL_Texture*, SDL_Rect> tileRectMap,
            std::vector<std::pair<int, int >> platformPositions, std::vector<std::pair<std::pair<int, int >, std::string>> doors);
    //~Room();
    void render(Renderer &renderer);

    vec_t anchor; //where the base (bottom left) of the room is located in global space
    RoomRep rep;
    void fillPlatformVector(std::vector<std::shared_ptr<Platform>>& p);
    void fillDoorVector(std::vector<std::shared_ptr<Gate>>& g);
    void fillEnemyVector(std::vector<std::shared_ptr<Enemy>>& e);
    void fillBossVector(std::vector<std::shared_ptr<Boss>>& b);

    void printP();
    SDL_Rect backgroundRectangle;
    SDL_Texture* backgroundtexture;
    std::unordered_map<SDL_Texture*, SDL_Rect> tileMap;
    std::vector<std::pair<int, int >> platformPositions;
    std::vector<std::pair<int, int >> wallPostitions;
    std::vector<std::pair<int, int >> ceilingPositions;
    std::vector<std::pair<int, int >> floorPositions;
    std::vector<std::pair<std::pair<int, int >, std::string>> doorPositions;
    std::vector<std::pair<std::pair<int, int >, int>> enemyInformation;
    std::vector<std::pair<std::pair<int, int >, int>> bossInformation;
    std::pair<int, int> newStartPosition;
    int roomId;
    int musicId = -1;
    std::vector<gateInformation> gates;
    std::vector<LockedWall> lockedWalls;
    std::vector<EnemyInformation> enemies;
    Vec2<int> position;

    void clear();
};
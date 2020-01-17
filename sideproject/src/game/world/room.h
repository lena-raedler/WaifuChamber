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
#include "../utils/image.h"
#include <unordered_map>
#include <utility>

enum TileType{
    BLANK,
    SEMISOLID,
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
    Room(SDL_Texture* texture, SDL_Rect rectangle, std::unordered_map<SDL_Texture*, SDL_Rect> tileRectMap);
    //~Room();
    void render(Renderer &renderer);

    vec_t anchor; //where the base (bottom left) of the room is located in global space
    RoomRep rep;

private:
    SDL_Rect backgroundRectangle;
    SDL_Texture* backgroundtexture;
    std::unordered_map<SDL_Texture*, SDL_Rect> tileMap;

};
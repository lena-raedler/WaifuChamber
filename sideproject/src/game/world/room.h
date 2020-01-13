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

class Room {
public:
    Room();
    Room(SDL_Texture* texture, SDL_Rect rectangle, std::unordered_map<SDL_Texture*, SDL_Rect> tileRectMap);
    //~Room();
    void render(Renderer &renderer);

private:
    SDL_Rect backgroundRectangle;
    SDL_Texture* backgroundtexture;
    std::unordered_map<SDL_Texture*, SDL_Rect> tileMap;

};
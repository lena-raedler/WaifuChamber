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

class Room {
public:
    Room(std::string path);
    //~Room();
    void render(Renderer &renderer);

private:
    SDL_Rect backgroundRectangle;
    SDL_Surface* surface;
    SDL_Texture* texture;
    std::string texturePath;
    std::string path;
    void parseRoom();
};
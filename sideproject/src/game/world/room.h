//
// Created by lena on 1/1/20.
//

#pragma once

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "../utils/renderer.h"

class Room {
public:
    Room(std::string path);
    //~Room();
    //void render(std::unique_ptr<Renderer> &renderer);

private:
    //SDL_Texture* backgroundTexture;
    //SDL_Rect backgroundRectangle;
    //SDL_Surface* backgroundSurface;
    std::string path;
    void parseRoom();

};
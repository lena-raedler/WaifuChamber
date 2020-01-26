//
// Created by bnorb on 26.01.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "../utils/Image.hpp"
#include "../utils/utility.h"
#include "../GlobalConstants.h"
#include <memory>

class Slot {
public:
    Slot();
    Slot(const std::string& path, Renderer& renderer, Vec2<int> position);
    ~Slot();
    void renderSlot();
    void setAvailable(bool availableNew);

private:
    bool available;
    std::string path;
    Image image;
    SDL_Rect background;
    Vec2<int> position;
    Renderer* renderer;
    void changePath(const std::string& newPath);
};
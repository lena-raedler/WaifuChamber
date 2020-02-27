//
// Created by bnorb on 27.02.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../GlobalObjects.h"
#include "../utils/Image.h"

class MapTile {
public:
    MapTile();
    ~MapTile() = default;

    Image image;
};

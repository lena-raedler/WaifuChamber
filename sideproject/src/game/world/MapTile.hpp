//
// Created by bnorb on 27.02.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../GlobalObjects.h"
#include "../utils/Image.h"
#include "../utils/Vec2.h"
#include "../utils/utility.h"

class MapTile {
public:
    /// Constructor & Destructor ///
    MapTile();
    MapTile(Image image, Vec2<int> position);
    MapTile(Image image, Image imageHighlighted, Vec2<int> position);
    ~MapTile() = default;

    /// Fields ///
    Image image;
    Image imageHighlighted;
    Vec2<int> position;

    /// Functions ///
    void render();
    void renderHighlighted();
};

//
// Created by bnorb on 23.01.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class ImageNew {
public:
    ImageNew();
    ImageNew(SDL_Texture* texture, SDL_Rect rect);
    ~ImageNew();
    SDL_Texture* getTexture();
    SDL_Rect* getRect();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
};


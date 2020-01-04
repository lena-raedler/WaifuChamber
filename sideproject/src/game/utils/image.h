//
// Created by lena on 1/4/20.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Image {
    SDL_Texture* texture;
    int width;
    int height;

    Image(SDL_Texture* texture, int width, int height);
    Image() = default;
    ~Image();
};

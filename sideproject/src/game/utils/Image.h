//
// Created by bnorb on 23.01.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "renderer.h"
#include "../GlobalObjects.h"

class Image {
public:
    Image();
    Image(SDL_Texture* texture, SDL_Rect rect);
    ~Image();
    SDL_Texture* getTexture();
    SDL_Rect* getRect();
    void render(Renderer& renderer);
    void render();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
};
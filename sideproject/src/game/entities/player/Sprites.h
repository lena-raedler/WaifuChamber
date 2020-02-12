//
// Created by lena on 2/12/20.
//

#ifndef WAIFU_SPRITES_H
#define WAIFU_SPRITES_H

#include <vector>
#include <utility>
#include <iostream>
#include "../../utils/renderer.h"
#include <string>

class Sprites {
public:
    SDL_Texture* spriteSheet;
    std::vector<SDL_Rect> sprites;
    void render(Renderer& renderer, vec_t pos);

private:
    //for rendering purposes
    int maxFrame = 6;
    int currentFrame = 0;
    int activeSprite = 0;
};


#endif //WAIFU_SPRITES_H

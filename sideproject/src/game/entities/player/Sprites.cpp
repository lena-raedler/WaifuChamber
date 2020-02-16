//
// Created by lena on 2/12/20.
//

#include "Sprites.h"

void Sprites::render(Renderer &renderer, vec_t pos) {

    if(currentFrame++ >= maxFrame) {
        currentFrame = 0;
        ++activeSprite %= sprites.size(); //theoretically can be 0 !!
    }
    renderer.renderSprite(spriteSheet, pos, &sprites[activeSprite]);
}

void Sprites::render(Renderer &renderer, vec_t pos, int orientation) {
    std::vector<SDL_Rect> toRender;
    if(orientation < 0) {
        toRender = {sprites[0], sprites[1], sprites[2]};
    }
    if(orientation >= 0) {
        toRender = {sprites[3], sprites[4], sprites[5]};
    }
    //add idle position here
    if(currentFrame++ >= maxFrame) {
        currentFrame = 0;
        ++activeSprite %= toRender.size(); //theoretically can be 0 !!
    }
    renderer.renderSprite(spriteSheet, pos, &toRender[activeSprite]);

}
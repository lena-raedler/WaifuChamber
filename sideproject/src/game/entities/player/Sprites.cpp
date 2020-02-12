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

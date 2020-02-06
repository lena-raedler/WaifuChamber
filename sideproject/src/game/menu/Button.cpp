//
// Created by bnorb on 06.02.20.
//

#include "Button.hpp"

Button::Button(Renderer& renderer, std::string imagePath, int xTmp, int yTmp, int widthTmp, int heightTmp) {
    x = xTmp;
    y = yTmp;
    width = widthTmp;
    height = heightTmp;
    image = utility::loadImage(imagePath, renderer);
    image.getRect()->x = x;
    image.getRect()->y = y;
    image.getRect()->w = width;
    image.getRect()->h = height;
}

void Button::renderButton(Renderer& renderer) {
    image.render(renderer);

    // Gray background
    //SDL_SetRenderDrawColor(renderer.getRenderer(), 0x80, 0x80, 0x80, 0xFF);
    //SDL_RenderFillRect(renderer.getRenderer(), &background);

    //if(available)
    //itemImage.render(*renderer);
}

bool Button::inButton(int x2, int y2) {
    return (x <= x2 && x2 <= x+width) && (y <= y2 && y2 <= y+height);
}
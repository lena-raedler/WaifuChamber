//
// Created by bnorb on 06.02.20.
//

#include "Button.hpp"

Button::Button(Renderer& renderer, std::string imagePath, std::string imagePathHighlighted, int xTmp, int yTmp, int widthTmp, int heightTmp) {
    x = xTmp;
    y = yTmp;
    width = widthTmp;
    height = heightTmp;
    image = utility::loadImage(imagePath, renderer);
    imageHighlighted = utility::loadImage(imagePathHighlighted, renderer);
    image.getRect()->x = imageHighlighted.getRect()->x = x;
    image.getRect()->y = imageHighlighted.getRect()->y = y;
    image.getRect()->w = imageHighlighted.getRect()->w = width;
    image.getRect()->h = imageHighlighted.getRect()->h = height;
    highlighted = false;
    clicked = false;
    soundEffect.load("button_press_1.wav", MIX_MAX_VOLUME);
}

void Button::renderButton(Renderer& renderer) {
    if (highlighted)
        imageHighlighted.render(renderer);
    else
        image.render(renderer);

    if (clicked) {
        soundEffect.play();
        clicked = false;
    }
}

bool Button::inButton(int x2, int y2) {
    return (x <= x2 && x2 <= x+width) && (y <= y2 && y2 <= y+height);
}
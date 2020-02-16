//
// Created by bnorb on 16.02.20.
//

#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>
#include "PositionSize.hpp"
#include "../GlobalObjects.h"
#include "utility.h"

enum FontType {
    FreeSerif
};

class Text {
public:
    Text();
    Text(std::string message);
    Text(std::string message, int fontSize, SDL_Color textColor);
    Text(std::string message, std::string fontPath, int fontSize, SDL_Color textColor);
    Text(std::string message, std::string fontPath, int fontSize, SDL_Color textColor, int x, int y);
    //Text(FontType type);
    ~Text() = default;
    TTF_Font* font;
    std::string message;
    int fontSize;
    SDL_Color messageColor = {0, 0, 0};
    PositionSize positionSize;
    SDL_Rect rect;
    SDL_Texture* fontTexture = nullptr;
    void changeText(std::string newText);
    void changeFontSize(int newFontSize);
    void changeColor(SDL_Color newMessageColor);
    void changeText(std::string newText, int newFontSize, SDL_Color newTextColor);
    void loadText();
    void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
};

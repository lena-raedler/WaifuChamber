//
// Created by bnorb on 27.01.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "../../utils/renderer.h"
#include "../../utils/Rgba.hpp"

class Bar {
public:
    //Bar() = default;
    //Bar(int x, int y, int width, int height, Rgba borderColor, Rgba barColor);
    //Bar(Bar& bar) = default;
    //Bar(Bar&& bar) = default;
    ~Bar() = default;
    void updateBar(double percentageRemaining);
    void renderBar(Renderer& renderer);

//private:
    int x, y, width, height;
    SDL_Rect healthBarBorderRect;
    SDL_Rect healthBarBackgroundRect;
    SDL_Rect healthBarRect;
    Rgba borderColor;
    Rgba barColor;
};

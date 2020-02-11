//
// Created by bnorb on 27.01.20.
//

#include "Bar.hpp"

//Bar::Bar() {
//}

/*
Bar::Bar(int x, int y, int width, int height, Rgba borderColor, Rgba barColor)
    : x(x)
    , y(y)
    , width(width)
    , height(height)
    , borderRect({x, y, width, height})
    , backgroundRect({x+5, y+5, width-10, height-10})
    , barRect({x+5, y+5, width-10, height-10})
    , borderColor(borderColor)
    , barColor(barColor)
{}
*/

void Bar::updateBar(double percentageRemaining) {
    barRect.w = std::clamp(percentageRemaining, 0.0, 1.0) * backgroundRect.w;
}

void Bar::renderBar(Renderer& renderer) {
    // Light red
    //SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x80, 0x80, 0xFF);
    SDL_SetRenderDrawColor(renderer.getRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderFillRect(renderer.getRenderer(), &borderRect);

    // Black
    SDL_SetRenderDrawColor(renderer.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer.getRenderer(), &backgroundRect);

    // Red; Draw as much as the player has hp left.
    //SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawColor(renderer.getRenderer(), barColor.r, barColor.g, barColor.b, barColor.a);
    SDL_RenderFillRect(renderer.getRenderer(), &barRect);
}
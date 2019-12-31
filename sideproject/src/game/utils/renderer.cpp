//
// Created by lena on 11/10/19.
// wrapper class for SDL_Renderer
//

#include "renderer.h"
#include <iostream>

Renderer::Renderer() {
    window = SDL_CreateWindow("Waifu Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);     // TODO Width and height should be variables, not static numbers (see game.h)
    if(!window) {
        std::cerr << "failed to create window" << std::endl;
        throw  std::runtime_error("Could not open window");
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cerr << "failed to create renderer" << std::endl;
        throw std::runtime_error("Could not create renderer");
    }
}

Renderer::~Renderer() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if(window) {
        SDL_DestroyWindow(window);
    }
}

void Renderer::render() {
    SDL_RenderPresent(renderer);
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface *surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}

void Renderer::renderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::renderTexture(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect) {
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}
void Renderer::renderBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) {
    Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
    SDL_Color old;
    SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
    SDL_Rect bgrect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(renderer, &bgrect);
    SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int)((float)w * Percent);
    int px = x + (w - pw);
    SDL_Rect fgrect = { px, y, pw, h };
    SDL_RenderFillRect(renderer, &fgrect);
    SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
}

SDL_Color Renderer::color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color col = {r,g,b,a};
    return col;
}
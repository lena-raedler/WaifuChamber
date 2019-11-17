//
// Created by lena on 11/10/19.
// wrapper class for SDL_Renderer
//

#include "renderer.h"
#include <stdio.h>
#include <iostream>

Renderer::Renderer() {
    window = SDL_CreateWindow("Waifu Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cerr << "failed to create window" << std::endl;
        throw  std::runtime_error("Could not open window");
    }
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
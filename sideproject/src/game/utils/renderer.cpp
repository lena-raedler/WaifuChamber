//
// Created by lena on 11/10/19.
//

#include "renderer.h"
#include <stdio.h>
#include <iostream>

Renderer::Renderer() {
    std::cerr << "const" << std::endl;
    window = SDL_CreateWindow("Waifu Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    std::cerr << "am i dying here" << std::endl;
    if(!window) {
        std::cerr << "failed to create window" << std::endl;
        throw  std::runtime_error("Could not open window");
    }
    std::cerr << "what about here" << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    std::cerr << "say penis" << std::endl;
    if(!renderer) {
        std::cerr << "failed to create renderer" << std::endl;
        throw std::runtime_error("Could not create renderer");
    }
    std::cerr << "end const" << std::endl;
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
    std::cerr << "render" << std::endl;
    SDL_RenderPresent(renderer);
}

void Renderer::clear() {
    //std::cerr << "clear" << std::endl;
    SDL_RenderClear(renderer);
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface *surface) {
    std::cerr << "creating texture" << std::endl;
    return SDL_CreateTextureFromSurface(renderer, surface);
    /*SDL_Texture* newTexture = NULL;
    if(!surface) {
        std::cout << "error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Could not load texture");
    }
    newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!newTexture) {
        std::cout << "error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return newTexture;*/
}

void Renderer::renderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    //std::cerr << "color" << std::endl;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::renderTexture(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect) {
    //std::cerr << "render texture" << std::endl;
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}
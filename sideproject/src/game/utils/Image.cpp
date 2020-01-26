//
// Created by bnorb on 23.01.20.
//

#include "Image.hpp"

Image::Image() {}

Image::Image(SDL_Texture* textureTmp, SDL_Rect rectTmp)
        : texture(textureTmp)
        , rect(rectTmp)
        {}

Image::~Image() {
    // Gets called too early and destroys the texture while still in use(?)
    //SDL_DestroyTexture(texture);
}

SDL_Texture* Image::getTexture() {
    return texture;
}

SDL_Rect* Image::getRect() {
    return &rect;
}

void Image::render(Renderer& renderer) {
    renderer.renderTexture(texture, nullptr, &rect);
}
//
// Created by bnorb on 23.01.20.
//

#include "ImageNew.hpp"

ImageNew::ImageNew() {}

ImageNew::ImageNew(SDL_Texture* textureTmp, SDL_Rect rectTmp)
        : texture(textureTmp)
        , rect(rectTmp)
        {}

ImageNew::~ImageNew() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* ImageNew::getTexture() {
    return texture;
}

SDL_Rect* ImageNew::getRect() {
    return &rect;
}
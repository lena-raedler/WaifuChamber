//
// Created by lena on 1/4/20.
//

#include "image.h"

Image::Image(SDL_Texture *texture, int width, int height) :
    texture(texture),
    width(width),
    height(height) {}

Image::~Image() {
    SDL_DestroyTexture(texture);
}

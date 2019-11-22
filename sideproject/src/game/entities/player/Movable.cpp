//
// Created by auki on 22.11.19.
//

#include "Movable.h"
const void Movable::render(Renderer &renderer) {
    //do something
}

const std::string Movable::getTextureLocation() {
    return textureLocation;
}
void Movable::move(double delta){
    position += velocity * delta;
}
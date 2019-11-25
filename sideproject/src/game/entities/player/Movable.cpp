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
vec_t Movable::gravity(){
    switch(gravityType){
        case NORMAL:
            return{0, 1};
        default:
            return{0, 0.1};
    }
}
void Movable::move(double delta){
    velocity += gravity();
    position += velocity * delta;
    position.y = std::clamp(position.y, 0.0, 200.0); //jank platform
    rec->x = position.x;
    rec->y = position.y;
    //TODO handle collisions

}
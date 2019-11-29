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
    value_t grav;
    switch(gravityType){
        case NORMAL:
            grav = isFalling ? 1 : 0;
            break;
        default:
            grav = isFalling ? 0.01 : 0;
            break;
    }
    return {0, grav};
}
void Movable::move(double delta){
    velocity.y = std::clamp(velocity.y, -100.0, 10.0);
    velocity += gravity();
    position += velocity * delta;
    position.y = std::clamp(position.y, 0.0, 200.0); //jank platform
    rec->x = position.x;
    rec->y = position.y;
    //TODO handle collisions

}
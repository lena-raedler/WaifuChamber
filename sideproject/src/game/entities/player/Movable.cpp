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
            grav = isFalling ? gravityConstant : 0;
            break;
        default:
            grav = isFalling ? gravityConstant : 0;
            break;
    }
    return {0, grav};
}
void Movable::move(double delta){//this is jank TODO fix
    velocity.y = std::clamp(velocity.y, -5000.0, 50.0);
    velocity += gravity()*delta;

    position += velocity * delta;

    position.y = std::clamp(position.y, 0.0, 200.0); //jank platform

    rec->x = position.x;
    rec->y = position.y;
    //TODO handle collisions

}
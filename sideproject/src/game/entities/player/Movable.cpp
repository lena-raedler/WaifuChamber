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
    std::cout << "1" << std::endl;
    velocity.y = std::clamp(velocity.y, -5000.0, 50.0);

    std::cout << "2" << std::endl;
    velocity += gravity()*delta;

    std::cout << "3" << std::endl;
    position += velocity * delta;

    std::cout << "4" << std::endl;
    position.y = std::clamp(position.y, 0.0, 200.0); //jank platform

    std::cout << "5" << std::endl;
    rec->x = position.x;

    std::cout << "6" << std::endl;
    rec->y = position.y;
    //TODO handle collisions

}
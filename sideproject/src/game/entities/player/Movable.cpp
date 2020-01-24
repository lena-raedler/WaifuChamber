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
void Movable::move(double delta, std::vector<Platform>* platforms){//this is jank TODO fix
    if(usesPlatforms) {
        maxPos = {std::numeric_limits<value_t>::min(), std::numeric_limits<value_t>::min()};
        minPos = {std::numeric_limits<value_t>::max(), std::numeric_limits<value_t>::max()};
        for (triangle t : hitbox) {
            maxPos.max(t.max());
            minPos.min(t.min());
        }
    }

    velocity.y = std::clamp(velocity.y, -5000.0, 50.0);

    velocity += gravity()*delta;

    vec_t projPosition = position;
    projPosition += (velocity*delta);

    if(usesPlatforms && platforms != NULL){
        bool insidePlatform = false;
        for(Platform p : *platforms){
            auto direction = p.direction(*this);
            for(triangle t : hitbox) {
                insidePlatform = insidePlatform || p.collide(t);
                if(insidePlatform){
                    projPosition.y = p.top.min().y; //maybe add epsilon idk
                    insidePlatform = false;
                    velocity.y = 0;
                }

            }
            //TODO fix this jank

        }
        position = projPosition;

    }
    else{
        position = projPosition;
    }

    rec->x = position.x;

    std::cout << "6" << std::endl;
    rec->y = position.y;
    //TODO handle collisions

}
bool Movable::onPlatform(Platform& p){

}
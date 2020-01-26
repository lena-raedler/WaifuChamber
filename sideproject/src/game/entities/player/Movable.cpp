//
// Created by auki on 22.11.19.
//

#include "Movable.h"
#include "../../GlobalObjects.h"

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
void Movable::move(double delta){
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

    if(usesPlatforms){
        for(Platform p : GlobalObjects::platforms){
//            auto direction = p.direction(*this);
            for(triangle t : hitbox) {
                t.a += position;
                t.b += position;
                t.c += position;
                if(p.collide(t)){
                    switch(p.type){
                        case PLATFORM :
                            if(position.y <= p.top.min().y) {//above
                                grounded();
                                projPosition.y = p.top.min().y - GlobalConstants::tileSize; //maybe add epsilon idk
                                if(velocity.y > 0){
                                    velocity.y = 0;
                                }
                                else{
                                    projPosition.y += velocity.y*delta;
                                }
                            }
                            else{//below
                                velocity.y = 0;
                                projPosition.y = p.top.max().y + GlobalConstants::epsilon;
                            }
                            break;
                        case WALL :
                            if(position.x <= p.top.min().x) {//above
                                projPosition.x = p.top.min().x - GlobalConstants::tileSize; //maybe add epsilon idk
                                if(velocity.x > 0){
                                    velocity.x = 0;
                                }
                                else{
                                    projPosition.x += velocity.x*delta;
                                }
                            }
                            else{//below
                                projPosition.x = p.top.max().x;
                                if(velocity.x < 0){
                                    velocity.x = 0;
                                }
                                else{
                                    projPosition.x += velocity.x*delta;
                                }

                            }
                            break;
                        case CEILING :
                            velocity.y = 0;
                            projPosition.y = p.top.max().y + GlobalConstants::epsilon;
                            break;
                        case FLOOR :
                            grounded();
                            projPosition.y = p.top.min().y - GlobalConstants::tileSize; //maybe add epsilon idk
                            if(velocity.y > 0){
                                velocity.y = 0;
                            }
                            else{
                                projPosition.y += velocity.y*delta;
                            }
                            break;
                        default:
                            break;
                    }
                }

            }
        }


    }
    position = projPosition;

    rec->x = position.x;

    rec->y = position.y;

}
bool Movable::onPlatform(Platform& p){
    return true;

}
void Movable::grounded(){

}
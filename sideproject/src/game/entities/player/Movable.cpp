//
// Created by auki on 22.11.19.
//

#include "Movable.h"
#include "../../GlobalObjects.h"

const void Movable::render(Renderer &renderer) {
    SDL_Surface* surface = IMG_Load(textureLocation.c_str());
    SDL_Texture* texture = renderer.createTextureFromSurface(surface);
    {
        SDL_Rect r = {(int)position.x, (int)position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        rec = std::make_shared<SDL_Rect>(r);
    }
    renderer.renderTexture(texture, nullptr, rec.get());
    SDL_FreeSurface(surface);
}

const std::string Movable::getTextureLocation() {
    return textureLocation;
}
vec_t Movable::gravity(){
    value_t grav;
    switch(gravityType){
        case NORMAL:
            grav =  gravityConstant;
            break;
        case NOGRAVITY :
            grav = 0;
            break;
        default:
            grav = gravityConstant;
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
        double xMax = std::numeric_limits<double>::min();
        double yMax = std::numeric_limits<double>::min();
        for(triangle& t :hitbox ){//todo remove this
            vec_t tmp = t.max();
            xMax = std::max(xMax, tmp.x);
            yMax = std::max(yMax, tmp.y);
        }
        for(auto& p : GlobalObjects::platforms){

//            auto direction = p.direction(*this);
            for(triangle t : hitbox) {
                t += position;
                bool collide = p->collide(t);
                if(fragile && collide){
                    alive = false;
                    return;
                }
                if(collide){
                    switch(p->type){
                        case PLATFORM :
                            if(position.y <= p->top.min().y) {//above
                                grounded(delta);
                                projPosition.y = p->top.min().y - yMax; ; //maybe add epsilon idk
                                if(velocity.y > 0){
                                    velocity.y = 0;
                                }
                                else{
                                    projPosition.y += velocity.y*delta;
                                }
                            }
                            else{//below
                                velocity.y = 0;
                                projPosition.y = p->top.max().y + GlobalConstants::epsilon;
                            }
                            break;
                        case WALL :
                            if(position.x <= p->top.min().x) {//above
                                projPosition.x = p->top.min().x - xMax; //maybe add epsilon idk
                                if(velocity.x > 0){
                                    velocity.x = 0;
                                }
                                else{
                                    projPosition.x += velocity.x*delta;
                                }
                            }
                            else{//below
                                projPosition.x = p->top.max().x;
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
                            projPosition.y = p->top.max().y + GlobalConstants::epsilon;
                            break;
                        case FLOOR :
                            grounded(delta);
                            projPosition.y = p->top.min().y - yMax; //maybe add epsilon idk
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
    position.y = std::clamp(position.y, 0.0, 2000.0);

    /*
    rec->x = position.x;

    rec->y = position.y;
     */

}
bool Movable::onPlatform(Platform& p){
    return true;

}
void Movable::grounded(double delta) {

}
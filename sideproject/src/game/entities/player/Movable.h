//
// Created by auki on 22.11.19.
//

#ifndef WAIFU_MOVABLE_H
#define WAIFU_MOVABLE_H
#include "../../utils/Vec2.h"
#include "../../utils/renderer.h"
#include <iostream>
#include <string>
#include <utility>


enum GravityType{
    NORMAL,
    NOGRAVITY,
    INVERTED,
    SOMEOTHERBSCATEGORYTHATIJUSTMAKEUPFORABSOLUTELYNOREASON
};
class Movable {
public:
    const void render(Renderer& renderer);
    const std::string getTextureLocation();
    vec_t position;
    vec_t velocity;
    GravityType gravityType;
    void move(double delta);
    std::string textureLocation;

};


#endif //WAIFU_MOVABLE_H

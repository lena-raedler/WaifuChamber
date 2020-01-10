//
// Created by auki on 22.11.19.
//

#ifndef WAIFU_MOVABLE_H
#define WAIFU_MOVABLE_H
#include "../../utils/Vec2.h"
#include "../../utils/renderer.h"
#include "../../utils/utility.h"
#include <algorithm>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <vector>


enum GravityType{
    NORMAL,
    NOGRAVITY,
    INVERTED,
    SOMEOTHERBSCATEGORYTHATIJUSTMAKEUPFORABSOLUTELYNOREASON
};
class Movable {
public:
    Movable() = default;
    Movable(const Movable&) = default;
    Movable(Movable&&) = default;


    int health = 1;
    bool iframes;//switch this on for iframes/static objects like bullets
    const void render(Renderer& renderer);
    const std::string getTextureLocation();
    std::shared_ptr<SDL_Rect> rec;
    double gravityConstant = 5;
    vec_t position;
    vec_t velocity {0, 0};
    bool isFalling;
    GravityType gravityType;
    void move(double delta);
    std::string textureLocation;
    std::vector<triangle> hitbox; //RELATIVE!!!!!!
    vec_t gravity();

};


#endif //WAIFU_MOVABLE_H

//
// Created by auki on 11.02.20.
//

#ifndef WAIFU_TELEGRAPHEDATTACK_H
#define WAIFU_TELEGRAPHEDATTACK_H
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
#include "../../GlobalConstants.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Projectile.hpp"
#include "../../world/Platform.h"

class TelegraphedAttack {
public:
    double damage;

    int x, y, w, h;

    SDL_Rect rect;

    double time = 0;
    double maxTime = 20;
    double lingering = 1;

    int aimed = 0; // 0 = no, 1 = x, 2 = y, 3 = x && y

    bool fired = false;
    void fire();

    void render(Renderer& renderer);
    void spawn();

    void update(double delta);


    void set(int ax, int ay, int aw, int ah);
};


#endif //WAIFU_TELEGRAPHEDATTACK_H

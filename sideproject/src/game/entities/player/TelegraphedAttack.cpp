//
// Created by auki on 11.02.20.
//

#include "TelegraphedAttack.h"
#include "../../GlobalObjects.h"

void TelegraphedAttack::fire(){
    Projectile p;
    p.position ={static_cast<double>(x), static_cast<double>(y)};
    p.damage = damage;
    p.gravityType = NOGRAVITY;
    p.velocity ={0.0, 0.0};
    p.owner = HOSTILE;
    p.hitbox.push_back({{0.0,0.0},{0.0,static_cast<double>(h)},{static_cast<double>(w),0.0}});
    p.hitbox.push_back({{static_cast<double>(w),static_cast<double>(h)},{0.0,static_cast<double>(h)},{static_cast<double>(w),0.0}});
    p.timeToLive = lingering;
    p.usesPlatforms = false;
    p.rec = std::make_shared<SDL_Rect>(rect);
    GlobalObjects::projectiles.push_back(std::make_shared<Projectile>(p));
    std::cout << p.hitbox[0] << std::endl;
    std::cout << p.hitbox[1] << std::endl;
    std::cout << p.position << std::endl;
}

void TelegraphedAttack::render(Renderer& renderer){
    SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 0, 0, 120);
    SDL_Rect tmp = rect;
    if(rect.w > rect.h){
        tmp.w *= (time/maxTime);
    } else{
        tmp.h *= (time/maxTime);
    }
    SDL_RenderFillRect(renderer.getRenderer(), &tmp);
    SDL_RenderDrawLine(renderer.getRenderer(), x, y, x+w, y);
    SDL_RenderDrawLine(renderer.getRenderer(), x+w, y, x+w, y+h);
    SDL_RenderDrawLine(renderer.getRenderer(), x, y, x, y+h);
    SDL_RenderDrawLine(renderer.getRenderer(), x, y+h, x+w, y+h);

}

void TelegraphedAttack::spawn(){
    GlobalObjects::telegraphedAttacks.push_back(*this);
}
void TelegraphedAttack::update(double delta){
    time += delta;
}
void TelegraphedAttack::set(int ax, int ay, int aw, int ah){
    x = ax;
    y = ay;
    w = aw;
    h = ah;
    rect = {x, y, w, h};
}
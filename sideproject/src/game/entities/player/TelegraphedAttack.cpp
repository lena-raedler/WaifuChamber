//
// Created by auki on 11.02.20.
//

#include "TelegraphedAttack.h"
#include "../../GlobalObjects.h"

void TelegraphedAttack::fire(){

}

void TelegraphedAttack::render(Renderer& renderer){
    SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 0, 0, 120);
    SDL_Rect tmp = rect;
    if(rect.w > rect.h){
        tmp.w /= (time/maxTime);
    } else{
        tmp.h /= (time/maxTime);
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
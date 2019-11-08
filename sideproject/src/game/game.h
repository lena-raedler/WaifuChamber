//
// Created by lena on 11/8/19.
//

#ifndef WAIFUCHAMBER_GAME_H
#define WAIFUCHAMBER_GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


class Game {
public:
    Game();
    ~Game();
    int loop();

private:
    void render();
    SDL_Window* window;
    SDL_Renderer* renderer;

};


#endif //WAIFUCHAMBER_GAME_H

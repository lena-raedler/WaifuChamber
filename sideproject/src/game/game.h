//
// Created by lena on 11/8/19.
//

#ifndef WAIFUCHAMBER_GAME_H
#define WAIFUCHAMBER_GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <memory>
#include "utils/renderer.h"


class Game {
public:
    Game();
    ~Game();
    int loop();

private:
    void render();
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Event e;
    SDL_Rect rectangle;
    std::unique_ptr<Renderer> renderer;
    bool quit;
    SDL_Surface* surface;

};


#endif //WAIFUCHAMBER_GAME_H

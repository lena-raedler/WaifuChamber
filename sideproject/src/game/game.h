//
// Created by lena on 11/8/19.
//

#ifndef WAIFUCHAMBER_GAME_H
#define WAIFUCHAMBER_GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>


class Game {
public:
    Game();
    ~Game();
    int loop();

private:
    void render();
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event e;
    SDL_Rect rectangle;
    bool quit;
    SDL_Texture* loadTexture(std::string path);

};


#endif //WAIFUCHAMBER_GAME_H

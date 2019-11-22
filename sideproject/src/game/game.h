//
// Created by lena on 11/8/19.
//

#ifndef WAIFUCHAMBER_GAME_H
#define WAIFUCHAMBER_GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <memory>
#include "utils/vec2.h"
#include "utils/renderer.h"
#include "entities/player/player.h"
#include <utility>


class Game {
public:
    Game();
    ~Game();
    int loop();

private:
    void render();
    void processInput();
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Event e;
    SDL_Rect rectangle;
    std::unique_ptr<Renderer> renderer;
    bool quit;
    SDL_Surface* surface;
    Player player;
    bool left;
    bool right;
    bool up;
    bool isFalling;
    const int speed = 300;
    vec2 playerPosition;
    int screenHeight = 480;
    int screenWidth = 640;
    const int jumpHeight = 10;
    int jump = 0;

};


#endif //WAIFUCHAMBER_GAME_H

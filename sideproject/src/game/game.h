//
// Created by lena on 11/8/19.
//

#ifndef WAIFUCHAMBER_GAME_H
#define WAIFUCHAMBER_GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <memory>
#include "utils/Vec2.h"
#include "utils/renderer.h"
#include "entities/player/player.h"
#include "utils/InputManager.h"
#include <utility>
#include "utils/utility.h"


class Game {
public:
    Game();
    ~Game();
    int loop();

private:
    InputManager inputManager;
    void render();
    void renderHealthBar();
    void processInput(double delta);
    vec_t determineInput(double delta);
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
    const int speed = 10;
    vec_t playerPosition;
    int screenHeight = 900;     // Original: 480
    int screenWidth = 1700; // Original: 640
    const int jumpHeight = 10;
    int jump = 0;
    void debugshit();//1st statement that is executed, do all kinds of testing in this
    SDL_Rect healthBarBorderRect;   // If this is defined after background then a SEGFAULT occurs(??)
    SDL_Texture* background;
    SDL_Rect healthBarRect;
};


#endif //WAIFUCHAMBER_GAME_H

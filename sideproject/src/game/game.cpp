//
// Created by lena on 11/8/19.
//

#include "game.h"

#include <iostream>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


Game::Game() {
    //initialize SDL components here
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Couldn't inititalize SDL" << std::endl;
        throw std::runtime_error("Couldn't initialize SDL");
    }
    window = SDL_CreateWindow("Waifu Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        throw std::runtime_error("Could not create window");
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        throw std::runtime_error("Could not create renderer");
    }
}

Game::~Game() {
    //close all SDL components here
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Game::loop() {
    while(1) {
        render();
    }
    return 0;
}


void Game::render() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}
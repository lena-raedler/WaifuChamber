//
// Created by lena on 11/8/19.
//

#include "game.h"

#include <iostream>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>


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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // initialize img loading
    int imageFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imageFlags) & imageFlags)) {
        throw std::runtime_error("Could not initialize SDL_image");
    }

    // load texture
    texture = loadTexture("files/textures/test_player.png");
    quit = false;

    //create rectangle to load the texture onto
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 32;
    rectangle.h = 32;
}

Game::~Game() {
    //close all SDL components here
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int Game::loop() {
    while(!quit) {
        render();
    }
    return 0;
}


void Game::render() {

    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) {
            quit = true;
        }
    }
    SDL_RenderClear(renderer);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
    SDL_RenderPresent(renderer);
}

SDL_Texture* Game::loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if(!surface) {
        std::cout << "error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Could not load texture");
    }
    newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!newTexture) {
        std::cout << "error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return newTexture;
}
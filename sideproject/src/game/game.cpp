//
// Created by lena on 11/8/19.
//

#include "game.h"

#include <iostream>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include "utils/renderer.h"
#include <memory>


Game::Game() {
    //initialize SDL components here
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Couldn't inititalize SDL" << std::endl;
        throw std::runtime_error("Couldn't initialize SDL");
    }
    // initialize img loading
    int imageFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imageFlags) & imageFlags)) {
        throw std::runtime_error("Could not initialize SDL_image");
    }
    renderer = std::make_unique<Renderer>();
    renderer->renderColor(0, 0, 0, 0);
    // load texture
    surface = IMG_Load("files/textures/test_player.png");
    if(!surface) {
        throw std::runtime_error("Could not create surface");
    }
    texture = renderer->createTextureFromSurface(surface);
    if(!texture) {
        std::cerr << "last idea" << std::endl;
    }
    quit = false;

    //create rectangle to load the texture onto
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 32;
    rectangle.h = 32;
    std::cerr << "rectangle" << std::endl;
}

Game::~Game() {
    //close all SDL components here
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
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
    renderer->clear();
    //renderer.renderColor(0, 0, 0, 0);
    //SDL_RenderCopy(renderer, texture, NULL, &rectangle);
    renderer->renderTexture(texture, nullptr, &rectangle);
    //SDL_RenderPresent(renderer);
    renderer->render();
}
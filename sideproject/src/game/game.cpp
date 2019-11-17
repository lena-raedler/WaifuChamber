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
#include "entities/player/player.h"
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
    surface = IMG_Load(player.getTextureLocation().c_str());
    if(!surface) {
        throw std::runtime_error("Could not create surface");
    }
    texture = renderer->createTextureFromSurface(surface);
    if(!texture) {
        std::cerr << "could not create texture" << std::endl;
        throw std::runtime_error("Could not create texture");
    }
    quit = false;
    left = false;
    right = false;
    isFalling = false;
    playerPosition = player.getPlayerPosition();
    //create rectangle to load the texture onto
    rectangle.x = playerPosition.first;
    rectangle.y = playerPosition.second;
    rectangle.w = surface->w;
    rectangle.h = surface->h;
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
        processInput();
        render();
    }
    return 0;
}

void Game::processInput() {
    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.scancode) {
                    case SDL_SCANCODE_A:
                        left = true;
                        break;
                    case SDL_SCANCODE_D:
                        right = true;
                        break;
                    case SDL_SCANCODE_W:
                        up = true;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(e.key.keysym.scancode) {
                    case SDL_SCANCODE_A:
                        left = false;
                        break;
                    case SDL_SCANCODE_D:
                        right = false;
                        break;
                    default:
                        break;
                }
                break;
        }

        // x_velocity in which we move
        int x_velocity = 0;

        // check which buttons were pressed
        if(left && !right) {
            x_velocity = -speed;}
        if(right && !left) {
            x_velocity = speed;}

        // button has to be pressed to execute jump
        if(up && !left && !right) {
            if(jump >= jumpHeight || isFalling) {
                if(jump == 0) {
                    isFalling = false;
                    break;
                }
                jump--;
                playerPosition.second--;
                isFalling = true;
            } else if(jump <= 0 && isFalling) {
                jump = 0;
                isFalling = false;
                up = false;
            } else {
                jump++;
                playerPosition.second++;
            }
            std::cerr << playerPosition.second << std::endl;
        }

        // update the player position
        playerPosition.first += x_velocity / 60;
        player.updatePlayerPosition(playerPosition.first, playerPosition.second);

        // update rectangle from player position
        rectangle.x = playerPosition.first;
        rectangle.y = playerPosition.second;


        // TODO: add suitable collision detection -> this is just basic
        // collision detection with bounds
        if (playerPosition.first <= 0) playerPosition.first = 0;
        if (playerPosition.second <= 0) playerPosition.second = 0;
        if (playerPosition.first >= screenWidth - rectangle.w) playerPosition.first = screenWidth - rectangle.w;
        if (playerPosition.second >= screenHeight - rectangle.h) playerPosition.second = screenHeight - rectangle.h;


    }

}


void Game::render() {
    renderer->clear();
    renderer->renderTexture(texture, nullptr, &rectangle);
    renderer->render();
}
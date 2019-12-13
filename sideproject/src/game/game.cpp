//
// Created by lena on 11/8/19.
//

#include "game.h"

#include <iostream>
#include <cstdlib>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include "utils/renderer.h"
#include "entities/player/player.h"
#include <memory>


Game::Game() {
    debugshit();
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
        std::string survey_fname;
        std::string dir(__FILE__);
        dir = dir.substr(0, dir.find_last_of("\\/"));
        std::cout << "ERROR: File " << player.getTextureLocation() << " could not be loaded!" << std::endl;
        std::cout << "PWD: " << dir << std::endl;
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
    playerPosition = player.position;
    //create rectangle to load the texture onto

    rectangle.x = playerPosition.x;
    rectangle.y = playerPosition.y;
    rectangle.w = surface->w;
    rectangle.h = surface->h;
    player.rec = std::make_unique<SDL_Rect>(rectangle);
    inputManager.init();
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
    unsigned long long now = SDL_GetPerformanceCounter();
    unsigned long long last = 0;
    double deltaTime = 0;
    while(!quit) {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last)*1000 / (double)SDL_GetPerformanceFrequency() );
        //processInput(deltaTime);
        player.velocity.x *= 0.8;
        auto move = determineInput(1);


        player.velocity += move;
        player.velocity.x = std::clamp(player.velocity.x, -30.0, 30.0); //terminal velocities
        player.upkeep(deltaTime/100);
        render();
    }
    return 0;
}

vec_t Game::determineInput(double delta){
    vec_t out{0, 0};
    quit = !inputManager.update();

    // check which buttons were pressed
    if(inputManager.isPressed(KEY_A)) {
        out.x += -speed;}
    if(inputManager.isPressed(KEY_D)) {
        out.x += speed;}
    if(inputManager.isPressed(KEY_W)) {
        if (player.canJump()) {
            player.jump();
        }
    }

    return{out.x, out.y};
}

void Game::processInput(double delta){
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
                playerPosition.y--;
                isFalling = true;
            } else if(jump <= 0 && isFalling) {
                jump = 0;
                isFalling = false;
                up = false;
            } else {
                jump++;
                playerPosition.y++;
            }
            std::cerr << playerPosition.y << std::endl;
        }

        // update the player position
        playerPosition.x += x_velocity * delta /60;
        player.updatePlayerPosition(playerPosition.x, playerPosition.y);

        // update rectangle from player position
        rectangle.x = playerPosition.x;
        rectangle.y = playerPosition.y;


        // TODO: add suitable collision detection -> this is just basic
        // collision detection with bounds
        if (playerPosition.x <= 0) playerPosition.x = 0;
        if (playerPosition.y <= 0) playerPosition.y = 0;
        if (playerPosition.x >= screenWidth - rectangle.w) playerPosition.x = screenWidth - rectangle.w;
        if (playerPosition.y >= screenHeight - rectangle.h) playerPosition.y = screenHeight - rectangle.h;


    }

}

void Game::render() {
    renderer->clear();
    renderer->renderTexture(texture, nullptr, player.rec.get());
    renderer->render();
}
void Game::debugshit() {
    vec_t as{1,1};
    vec_t ae{-1, -1};
    vec_t bs{-1, 1};
    vec_t be{1, -1};
    triangle a{{0,0},{1,1},{0,1}};
    triangle b{{1,0},{0,1},{1,1}};
    std::cout << utility::triangleTriangleIntersection(a,b) << " " << utility::lineLineIntersection(as,ae,bs,be)<<std::endl;
}
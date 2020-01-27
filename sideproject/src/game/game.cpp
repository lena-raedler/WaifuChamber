//
// Created by lena on 11/8/19.
//

#include "game.h"

#include <iostream>
#include <cstdlib>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <string>
#include "utils/renderer.h"
#include "entities/player/player.h"
#include <memory>
#include "utils/blackmagic.h"
#include "world/room.h"
#include "GlobalObjects.h"
#include "world/Gate.h"
#include "entities/player/EnemyBuilder.h"

Mix_Music *gMusic = NULL;
namespace GlobalObjects{
    std::vector<Enemy> enemies;
    std::vector<Platform> platforms;
    Player* playerPtr = NULL;
    std::vector<Projectile> projectiles;
    std::vector<Gate> gates;
    std::pair<int, int> resolution;
    void clear(){
        enemies.clear();
        platforms.clear();
        projectiles.clear();
        gates.clear();
    }
}
////////////////////////////////////////////////////////////////
Game::Game()
    : pause(false)
{
    GlobalObjects::playerPtr = &player;
    debugshit();

    GlobalObjects::resolution.first = screenWidth;
    GlobalObjects::resolution.second = screenHeight;
    //initialize SDL components here
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cout << "Couldn't inititalize SDL" << std::endl;
        throw std::runtime_error("Couldn't initialize SDL");
    }
    // initialize img loading
    int imageFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imageFlags) & imageFlags)) {
        throw std::runtime_error("Could not initialize SDL_image");
    }
    renderer = std::make_unique<Renderer>(GlobalObjects::resolution);

    //init sound

    Mix_Init(MIX_INIT_MP3);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    gMusic=Mix_LoadMUS("files/music/Certain Plan.mp3");
    Mix_VolumeMusic(32);
    // White background
    renderer->renderColor(255, 255, 255, 0);

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
    currentRoom = "files/rooms/testroom.txt";

    room = utility::parseRoom(currentRoom, *renderer, GlobalObjects::resolution);
    fillGlobalObjects(room);

    quit = false;

    pauseImage = utility::loadImage("files/backgrounds/pauseTransparent.png", *renderer);

    left = false;
    right = false;
    isFalling = false;
    checkpoints.push_back(Checkpoint({50,50}, player));
    player.lastCP = &checkpoints[0];
    playerPosition = player.position;
    {
        triangle t{{0,  0},
                   {GlobalConstants::tileSize, 0},
                   {0,  GlobalConstants::tileSize}};
        player.hitbox.push_back(t);
    }
    {
        triangle t{{GlobalConstants::tileSize,  GlobalConstants::tileSize},
                   {GlobalConstants::tileSize, 0},
                   {0,  GlobalConstants::tileSize}};
        player.hitbox.push_back(t);
    }

    /*
    Enemy adam;
    adam.maxHealth = 100;
    adam.health = 100;
    adam.position ={300, 300};
    adam.velocity = {0,0};
    adam.gravityType = NORMAL;
    adam.usesPlatforms = true;
    {
        triangle t{{0,                         0},
                   {GlobalConstants::tileSize, 0},
                   {0,                         GlobalConstants::tileSize}};
                   adam.hitbox.push_back(t);
    }
    {
        triangle t{{GlobalConstants::tileSize,  GlobalConstants::tileSize},
                   {GlobalConstants::tileSize, 0},
                   {0,  GlobalConstants::tileSize}};
        adam.hitbox.push_back(t);
    }
    Ability supermegadeathlazor;
    Projectile lazor;
    lazor.gravityType = NOGRAVITY;
    lazor.usesPlatforms = false;
    lazor.damage = 1;
    lazor.baseInit();
    lazor.timeToLive = 1000;
    supermegadeathlazor.projectile = lazor;
    supermegadeathlazor.speed = 30;
    supermegadeathlazor.cooldown = 10;
    adam.abilities.push_back(supermegadeathlazor);
    GlobalObjects::enemies.push_back(adam);
     */
    EnemyBuilder::buildEnemy(GlobalObjects::enemies, 1, {10, 10});
    std::cout << GlobalObjects::enemies.size() << std::endl;

    //create rectangle to load the texture onto

    rectangle.x = playerPosition.x;
    rectangle.y = playerPosition.y;
    rectangle.w = surface->w;
    rectangle.h = surface->h;
    player.rec = std::make_unique<SDL_Rect>(rectangle);
    inputManager.init();

    healthBarBorderRect = {20, 20, 210, 30};
    healthBarBackgroundRect = {healthBarBorderRect.x + 5, healthBarBorderRect.y + 5, healthBarBorderRect.w - 10, healthBarBorderRect.h - 10};
    healthBarRect = {healthBarBorderRect.x + 5, healthBarBorderRect.y + 5, healthBarBorderRect.w - 50, healthBarBorderRect.h - 10};

    //inventory = Inventory(*renderer);
    player.inventory = Inventory(*renderer);
}

Game::~Game() {
    //close all SDL components here
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window); //TODO: fix segfault here
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int Game::loop() {
    int deltaDenom = 100;
    unsigned long long now = SDL_GetPerformanceCounter();
    unsigned long long last = 0;
    double deltaTime = 0;

    while(!quit) {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last)*1000 / (double)SDL_GetPerformanceFrequency() );

        // If the game is paused, no input shall be accepted, except for quit (escape) and unpause (p)
        if (pause) {
            determineInput(1);
            render();
            continue;
        }

        //processInput(deltaTime);
        player.velocity.x *= 0.8;
        auto move = determineInput(1);
        if(quit){
            break;
        }

        player.velocity += move;
        player.velocity.x = std::clamp(player.velocity.x, -30.0, 30.0); //terminal velocities
        player.upkeep(deltaTime/deltaDenom);
        for(Enemy& e : GlobalObjects::enemies){
            e.upkeep(deltaTime/deltaDenom);

        }

        for (Projectile& projectile : GlobalObjects::projectiles) {
            projectile.upkeep(deltaTime/deltaDenom);
            if(blackmagic::collide(projectile, player)){
                player.getHit(projectile.damage);
                projectile.alive = false;
            }
        }
        bool leave = false;
        for(Gate& gate : GlobalObjects::gates){
            for(triangle t : player.hitbox) {
                t+=player.position;
                if (gate.collide(t)) {
                    room.clear();
                    GlobalObjects::clear();
                    room = utility::parseRoom(gate.nextRoomPath, *renderer, GlobalObjects::resolution);
                    player.position = utility::convert(room.newStartPosition);
                    std::cout << "hey hey kids" << std::endl;
                    fillGlobalObjects(room);
                    leave = true;
                    break;
                }

            }
            if(leave){
                break;
            }
        }

        if(player.vit.hp <= 0){
            std::cout << "GIT GUD" << std::endl;
            player.kill();
        }

        // Update player
        // TODO Update player in a separate function
        //player.updatePlayer(playerPosition.x, playerPosition.y);

        render();
        cleanup();

    }
    return 0;
}

vec_t Game::determineInput(double delta){

    // First check escape and 'p' in case the game is paused
    quit = !inputManager.update();

    if(inputManager.isPressed(KEY_ESCAPE)){
        std::cout << "Quitting..." << std::endl;
        quit = true;
    }

    if (inputManager.isPressed(KEY_P)) {
        if (player.canPause()) {
            player.pause();
            pause = !pause;
            if (pause) {
                std::cout << "Game paused!" << std::endl;
            }
            else {
                std::cout << "Game unpaused :)" << std::endl;
                // TODO Unsure if needed
                inputManager.flush();   // Delete all input during pause
            }
        }
    }

    vec_t out{0, 0};

    // If the game is paused ignore all other input
    if (pause)
        return out;

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
    if(inputManager.isPressed(KEY_R)){//test
        player.rest();
    }
    if(inputManager.isPressed(KEY_T)) {
        if (player.inventory.estusFlask.canUse()) {
            player.inventory.estusFlask.use(player.inventory);
            player.rest();
        }
    }
    if(inputManager.isPressed(KEY_Y)) {     // QWERTY layout!
        if (player.inventory.estusFlask.canReset())
            player.inventory.estusFlask.reset(player.inventory);
    }
    if(inputManager.isPressed(KEY_F)){//test
        if(!player.iframes) {
            player.getHit(10);
        }
    }
    if(inputManager.isPressed(KEY_Q)){//test
        std::cout<< player.position << std::endl;
    }
    if(inputManager.isPressed(KEY_V)){
        if (player.canSpawnProjectile() && projs.size() < 5) {
            player.spawnProjectile();   // Set the cooldown timer

            // TODO Bad, was just to test
            Projectile projectile({100,200}, 0);
            projectile.imageNew = utility::loadImage("files/textures/weapons/Arrow.png", *renderer);
            projectile.rec = std::make_unique<SDL_Rect>();
            projectile.rec->x = 100;
            projectile.rec->y = 200;
            projectile.rec->w = 32;
            projectile.rec->h = 32;
            projectile.velocity.x = 10;
            //projectile.velocity.x *= 0.8;
            //projectile.velocity.x = std::clamp(projectile.velocity.x, -30.0, 30.0); //terminal velocities
            projs.push_back(projectile);

            //projs.push_back(Projectile());
            //projs[0].position = {100, 200};
            //projs.push_back(Projectile({100,200}, 0, 1));
            std::cout << "Projectile created at :" << projs[0].position.x << " " << projs[0].position.y << std::endl;
            triangle t{{0,  0},
                       {40, 0},
                       {0,  40}};
            //projs[0].hitbox.push_back(t);
            projs.back().hitbox.push_back(t);

        }
    }
    if(inputManager.isPressed(KEY_M)){
        if(Mix_PausedMusic() == 1)
            Mix_ResumeMusic();
        else if(!Mix_PlayingMusic()) {
            Mix_FadeInMusicPos(gMusic, -1,1000, 63);
            //Mix_PlayMusic(gMusic, -1);
        }
    }
    if(inputManager.isPressed(KEY_N)){
        Mix_PauseMusic();
    }
    if(inputManager.isPressed(KEY_K)){
        std::cout << savedVariables.test << std::endl;
        savedVariables.test = 1222;
    }
    if(inputManager.isPressed(KEY_J)){
        std::ofstream file("savegame.txt", std::ios::trunc);
        if (file.good()) {
            savedVariables.serialize(file);
        }
        file.close();
    }
    if(inputManager.isPressed(KEY_L)){
        std::ifstream file("savegame.txt");
        if(file.good()) {
            savedVariables.deSerialize(file);
        }
        file.close();
    }

    return{out.x, out.y};
}

void Game::render() {
    // Clear the renderer and print the background.
    renderer->renderColor(255, 255, 255, 0);
    renderer->clear();

    room.render(*renderer);

    // Render pause screen
    if (pause)
        pauseImage.render(*renderer);

    //renderer->renderColor(255, 255, 255, 255);
    //renderer->renderTexture(texture, nullptr, player.rec.get());
    //SDL_Color backgroundColor = Renderer::color(255, 255, 255, 0);

    // Unused
    //if (!SDL_SetTextureColorMod(background, 0, 0, 0))
    //    std::cerr << "Could not set background color" << std::endl;



    //inventory.renderInventory();
    player.inventory.renderInventory();

    // Render the player after the background
    renderer->renderTexture(texture, nullptr, player.rec.get());
    renderer->renderTriangles(player.hitbox, 255, 0, 0, player.position);

    for (Projectile& projectile : GlobalObjects::projectiles) {
        //renderer->renderTexture(projectile.imageNew.getTexture(), nullptr, projectile.rec.get());
        renderer->renderTriangles(projectile.hitbox, 255, 255, 255, projectile.position);
    }

    for (Platform& p : GlobalObjects::platforms){
        std::vector<triangle> t = {p.top, p.bot};
        renderer->renderTriangles(t, 0, 0, 0, {0,0});
    }
    for (Enemy& e : GlobalObjects::enemies){
        renderer->renderTriangles(e.hitbox,255, 255, 0,e.position);
    }
    for (Gate& g : GlobalObjects::gates){
        renderer->renderTriangles(g.hitbox, 0,255, 255, g.position);
    }

    // Update the remaining health percentage
    updateHealthBar();

    // Render the health bar according to how much hp is left
    renderHealthBar();
    //SDL_Color hpCol = Renderer::color(1, 1, 1, 1);
    //SDL_Color barBGCol = Renderer::color(1, 1, 1, 1);
    //renderer->renderBar(50, 50, 100, 10, 200, hpCol, barBGCol);

//    renderer->renderBar(50, 50, 100, 10, player.vit.hp/player.vit.maxHp, hpCol, barBGCol);
    renderer->render();
}

/*
 * For now only the health bar gets updated according to the remaining hp left (percentage)
 */
void Game::updateHealthBar() {
    healthBarRect.w = std::clamp(static_cast<double>(player.vit.healthPercentage()), 0.0, 1.0) * healthBarBackgroundRect.w;
}

/*
 * Render the health bar with simple colors (no textures) depending on how much life the player currently has.
 * The health bar consists of 3 overlapping parts: The background border, the background color and the health bar itself.
 * The background border is simply a lighter colored version of the health bar color, whereas the background is black
 * to give a good contrast.
 */
void Game::renderHealthBar() {
    // Light red
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0xFF, 0x80, 0x80, 0xFF);
    SDL_RenderFillRect(renderer->getRenderer(), &healthBarBorderRect);

    // Black
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer->getRenderer(), &healthBarBackgroundRect);

    // Red; Draw as much as the player has hp left.
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer->getRenderer(), &healthBarRect);
}

void Game::debugshit() {
    vec_t as{1,1};
    vec_t ae{-1, -1};
    vec_t bs{1, -1};
    vec_t be{-1, 1};
    triangle a{{0,0},{1,1},{0,1}};
    triangle b{{1,0},{0,1},{1,1}};
    std::cout << utility::triangleTriangleIntersection(a,b) << " " << utility::lineLineIntersection(as,ae,bs,be)<<std::endl;
}
void Game::cleanup(){
    {
        auto it = GlobalObjects::projectiles.begin();
        while (it != GlobalObjects::projectiles.end()) {

            if (!it->alive) {
                it = GlobalObjects::projectiles.erase(it);
            } else {
                ++it;
            }
        }
    }
    {
        auto it = GlobalObjects::enemies.begin();
        while (it != GlobalObjects::enemies.end()) {

            if (it->health <= 0) {
                it = GlobalObjects::enemies.erase(it);
            } else {
                ++it;
            }
        }
    }
}
void Game::fillGlobalObjects(Room& room){
    room.fillPlatformVector(GlobalObjects::platforms);
    room.fillEnemyVector(GlobalObjects::enemies);
    room.fillDoorVector(GlobalObjects::gates);
}


/*
int Game::renderInventory2(int argc, char *argv[]) {
    QApplication application(argc, argv);
    Calculator calculator;
    calculator.show();
    application.exec();
    application.quit();
}
*/
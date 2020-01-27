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
#include "entities/player/Boss.h"

Mix_Music *gMusic = NULL;
Mix_Music *gMusicBoss = NULL;
Mix_Music *gMusicVic = NULL;
namespace GlobalObjects{
    Mix_Chunk* chunkPtr[3];
    SavedVariables savedVariables;
    std::vector<Enemy> enemies;
    std::vector<Platform> platforms;
    Player* playerPtr = NULL;
    std::vector<Projectile> projectiles;
    std::vector<Gate> gates;
    std::pair<int, int> resolution;
    std::vector<Boss> bosses;
    void clear(){
        enemies.clear();
        platforms.clear();
        projectiles.clear();
        gates.clear();
        bosses.clear();
    }
}
////////////////////////////////////////////////////////////////
Game::Game()
    : pause(false)
{
    std::ifstream file("savegame.txt");
    if(file.good()) {
        GlobalObjects::savedVariables.deSerialize(file);
    }
    file.close();
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

    int result;
    Mix_Init(MIX_INIT_MP3);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    result = Mix_AllocateChannels(4);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
    }
    GlobalObjects::chunkPtr[0] = Mix_LoadWAV("files/sounds/scream.wav");
    GlobalObjects::chunkPtr[1] = Mix_LoadWAV("files/sounds/jump.wav");
    gMusic=Mix_LoadMUS("files/music/Hades - Scourge of the Furies 1.mp3");
    gMusicBoss=Mix_LoadMUS("files/music/Hades - Scourge of the Furies 2.mp3");
    gMusicVic=Mix_LoadMUS("files/music/Victory.mp3");
    Mix_VolumeMusic(66);
    Mix_PlayMusic(gMusic, -1);
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

    //Checkpoint* c2 = Checkpoint({1000,500}, player);
    //utility::fillDefaultHitbox(c2.hitbox);
    //checkpoints.push_back(Checkpoint({50,50}, player));
    //checkpoints.

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




    //create rectangle to load the texture onto

    rectangle.x = playerPosition.x;
    rectangle.y = playerPosition.y;
    rectangle.w = surface->w;
    rectangle.h = surface->h;
    player.rec = std::make_unique<SDL_Rect>(rectangle);
    inputManager.init();

    /*
    healthBarBorderRect = {20, 20, 210, 30};
    healthBarBackgroundRect = {healthBarBorderRect.x + 5, healthBarBorderRect.y + 5, healthBarBorderRect.w - 10, healthBarBorderRect.h - 10};
    healthBarRect = {healthBarBorderRect.x + 5, healthBarBorderRect.y + 5, healthBarBorderRect.w - 50, healthBarBorderRect.h - 10};
    */

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
            projectile.textureLocation = "files/textures/weapons/projectile_01.png";
            projectile.upkeep(deltaTime/deltaDenom);
            if(projectile.owner == HOSTILE) {
                if (blackmagic::collide(projectile, player)) {
                    player.getHit(projectile.damage);
                    projectile.alive = false;
                }
            }else if (projectile.owner == PLAYER){
                for (Enemy &e : GlobalObjects::enemies) {
                    if (blackmagic::collide(projectile, e)) {
                        e.getHit(projectile.damage);
                        projectile.alive = false;
                    }
                }
                for (Boss &b: GlobalObjects::bosses) {
                    if (projectile.collide(b, false)) {
                        b.getHit(projectile.damage);
                        projectile.alive = false;
                    }
                }
            }
        }
        for(Boss& boss : GlobalObjects::bosses){
            boss.upkeep(deltaTime/deltaDenom);
        }
        bool leave = false;
        for(Gate gate : GlobalObjects::gates){
            for(triangle t : player.hitbox) {
                t+=player.position;
                if (gate.collide(t)) {
                    GlobalObjects::clear();
                    room = utility::parseRoom(gate.nextRoomPath, *renderer, GlobalObjects::resolution);
                    player.position = utility::convert(room.newStartPosition);
                    switch(room.roomId){
                        case 1: player.position=utility::convert({57, 28});
                        break;
                        case 2: player.position=utility::convert({2, 28});
                        break;
                        case 3: player.position=utility::convert({3, 4});
                        break;
                        default:
                            break;
                    }
                    std::cout << player.position << std::endl;
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
            GlobalObjects::clear();
            room = utility::parseRoom(player.lastCP->room, *renderer, GlobalObjects::resolution);
            fillGlobalObjects(room);
            player.kill();
        }
        if(!scuffed && room.roomId == 3 && !bossDefeated(1)) {

            scuffed = true;
            Mix_PlayMusic(gMusicBoss, -1);
            spawnBoss(800, 800);
        }

        if(scuff2 && GlobalObjects::bosses.size() == 0){
            Mix_PlayMusic(gMusicVic, 1);
            scuff2 = false;
        }

        // Update player
        // TODO Update player in a separate function
        //player.updatePlayer(playerPosition.x, playerPosition.y);

        std::cout << player.position << std::endl;
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
        player.position={50, 50};
    }
    if (inputManager.isPressed(KEY_C) || inputManager.isMousePressed(MOUSE_LEFT)) {
        if (player.canSpawnProjectile()) {
            player.spawnProjectile();   // Set the cooldown timer

            Projectile p;
            utility::fillDefaultHitbox(p.hitbox);
            p.damage = 20;
            p.timeToLive = 2000;
            p.usesPlatforms = false;
            p.fragile = true;
            p.gravityType = NOGRAVITY;
            p.owner = PLAYER;
            p.baseInit();

            Ability a;
            a.projectile = p;
            a.speed = 47;
            a.cooldown = 1000;
            //a.origin = {0, 0};
            a.aimed = false;
            abilities.push_back(a);

            //int mouse_x, mouse_y;
            //SDL_GetMouseState(&mouse_x, &mouse_y);
            //vec_t vec {mouse_x, mouse_y};
            //Vec2<double> vec2 {static_cast<double>(mouse_x), static_cast<double>(mouse_y)};
            //Vec2<double> vec2 {static_cast<double>(player.position.x ), static_cast<double>(player.position.y)};
            a.use({player.position});
            //std::cout << "mouse_x: " << mouse_x << "\tmouse_y: " << mouse_y << std::endl;
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
    //renderer->renderTexture(texture, nullptr, player.rec.get());
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
    for (Boss& b : GlobalObjects::bosses){
        scuff2 = true;
        renderer->renderTriangles(b.hitbox, 255, 0, 255, b.position);
        b.bars[0].renderBar(*renderer);
        //b.healthBar.renderBar(*renderer);
    }
    /*for(auto& i : GlobalObjects::enemies) {
        i.render(*renderer);
    }
    for(auto& i : GlobalObjects::projectiles) {
        i.render(*renderer);
    }*/

    // Update the remaining health percentage
    //updateHealthBar();
    player.healthBar.updateBar(player.vit.healthPercentage());

    // Render the health bar according to how much hp is left
    //renderHealthBar();
    player.healthBar.renderBar(*renderer);

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
                it->kill();
                it = GlobalObjects::enemies.erase(it);
            } else {
                ++it;
            }
        }
    }
    {
        auto it = GlobalObjects::bosses.begin();
        while (it != GlobalObjects::bosses.end()) {

            if (it->defeated) {
                it->kill();
                it = GlobalObjects::bosses.erase(it);
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

void Game::spawnBoss(int x, int y){
    Boss boss;
    Ability supermegadeathlazor;
    Projectile lazor;
    lazor.gravityType = NOGRAVITY;
    lazor.usesPlatforms = false;
    lazor.damage = 10;
    utility::fillDefaultHitbox(lazor.hitbox);
    lazor.timeToLive = 1200;
    supermegadeathlazor.projectile = lazor;
    supermegadeathlazor.speed = 30;
    supermegadeathlazor.cooldown = 10;
    supermegadeathlazor.origin = {GlobalConstants::tileSize/4, GlobalConstants::tileSize/4};
    boss.addAbility(supermegadeathlazor, 1, 1);
    //boss.addHealthBar(200);
    //boss.addHealthBar(100);
    boss.addHealthBar(200, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF});
    boss.addHealthBar(160, {0x80, 0xFF, 0x80, 0xFF}, {0x00, 0xFF, 0x00, 0xFF});
    boss.addHealthBar(120, {0x80, 0x80, 0xff, 0xFF}, {0x00, 0x00, 0xFF, 0xFF});
    //boss.healthBar ( {64, 900, 1500, 30, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}});
    boss.position ={(double)x, (double)y};
    boss.speed = 20;
    boss.id = 1;
    boss.velocity = {0,0};
    boss.gravityType = NORMAL;
    boss.usesPlatforms = true;
    utility::fillDefaultHitbox(boss.hitbox, 2);
    GlobalObjects::bosses.push_back(boss);
}

bool Game::bossDefeated(int i){
    int tmp = GlobalObjects::savedVariables.bossesDefeated >> (i - 1);
    return tmp & 1;
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
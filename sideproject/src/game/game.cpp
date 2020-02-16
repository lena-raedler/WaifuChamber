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
#include <boost/algorithm/string/compare.hpp>
#include "utils/renderer.h"
#include "entities/player/player.h"
#include <memory>
#include "utils/blackmagic.h"
#include "world/room.h"
#include "GlobalObjects.h"
#include "world/Gate.h"
#include "entities/player/EnemyBuilder.h"
#include "entities/player/Boss.h"
#include "entities/player/AbilityPicker.h"
#include "entities/player/TelegraphedAttack.h"
#include "world/MusicPlayer.h"

Mix_Music *gMusic = NULL;
Mix_Music *gMusicBoss = NULL;
Mix_Music *gMusicVic = NULL;
namespace GlobalObjects{
    Mix_Chunk* chunkPtr[3];
    SavedVariables savedVariables;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Platform>> platforms;
    Player* playerPtr = NULL;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<std::shared_ptr<Gate>> gates;
    std::pair<int, int> resolution;
    std::vector<std::shared_ptr<Boss>> bosses;
    std::vector<Checkpoint> allCheckpoints;
    std::vector<Checkpoint*> roomCheckpoints;
    std::vector<Ability> abilities;
    std::vector<TelegraphedAttack> telegraphedAttacks;
    std::shared_ptr<Renderer> renderPtr;
    MusicPlayer musicPlayer;
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
    currentRoom = "files/rooms/testroom.txt";
    musicVolume = 5;     // Unnecessary due to loadSavedVariables(). Still here as a safety measure for now.
    effectVolume = 5;
    volumeStep = 12;

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
    GlobalObjects::renderPtr = std::make_shared<Renderer>(GlobalObjects::resolution);
    renderer = GlobalObjects::renderPtr;

    player.init(*renderer);
    GlobalObjects::playerPtr = &player;
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
    loadSavedVariables();
    GlobalObjects::chunkPtr[0] = Mix_LoadWAV("files/sounds/scream.wav");
    GlobalObjects::chunkPtr[1] = Mix_LoadWAV("files/sounds/jump.wav");
    GlobalObjects::chunkPtr[2] = Mix_LoadWAV("files/sounds/smb_fireball.wav");
    Mix_VolumeChunk(GlobalObjects::chunkPtr[0], 100);
    Mix_VolumeChunk(GlobalObjects::chunkPtr[1], 15);
    Mix_VolumeChunk(GlobalObjects::chunkPtr[2], 80);
    initializeMusic();


    //musicVolume = 60;    // 5/10 on the musicVolume tracker, max = 128

    //std::cout << getVolume() << std::endl;

    //Mix_VolumeMusic(getMusicVolume());
    //Mix_PlayMusic(gMusic, -1);
    //Mix_Volume(-1, getVolume());     // MIX_MAX_VOLUME = 128
    Mix_Volume(-1, getEffectVolume());     // MIX_MAX_VOLUME = 128

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

    room = utility::parseRoom(currentRoom, *renderer, GlobalObjects::resolution);
    fillGlobalObjects(room, true);

    quit = false;

    pauseImage = utility::loadImage("files/backgrounds/pauseTransparent.png", *renderer);

    left = false;
    right = false;
    isFalling = false;

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
    //create rectangle to load the texture onto

    rectangle.x = playerPosition.x;
    rectangle.y = playerPosition.y;
    rectangle.w = surface->w;
    rectangle.h = surface->h;
    player.rec = std::make_unique<SDL_Rect>(rectangle);
    inputManager.init();

    player.inventory = Inventory(*renderer);

    // Menu
    menu = Menu(*renderer);
    menu.optionsMenu.musicVolume = musicVolume;
    menu.optionsMenu.effectVolume = effectVolume;
    menu.optionsMenu.debugActive = GlobalObjects::savedVariables.debugActive;

    /*
    int imageX = 64;
    int imageY = 64;
    int imageWidth = 824/4;
    int imageHeight = 82/2;

    healthBarImage = utility::loadImage("files/textures/menu/player/health_bar_cropped.png", *renderer);
    healthBarImage.getRect()->x = imageX;
    healthBarImage.getRect()->y = imageY;
    healthBarImage.getRect()->w = imageWidth;
    healthBarImage.getRect()->h = imageHeight;
     */

    // Enable opacity between 0 and 255
    SDL_SetRenderDrawBlendMode(renderer->getRenderer(), SDL_BLENDMODE_BLEND);
}
void Game::makeCheckpoints(){
    SDL_Surface* s = IMG_Load("files/textures/savepoint_01.png");
    {

        Checkpoint c;
        if(!c.texture) {
            std::cerr << SDL_GetError() << std::endl;
        }
        c.position = utility::convert({3, 6});
        utility::fillDefaultHitbox(c.hitbox);
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({55, 4});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/library.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({58, 1});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/plains.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({59, 32});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/fancy_forest.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({42, 13});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/desert1.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({9, 3});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/mazement1.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    SDL_FreeSurface(s);

    player.lastCP = &(GlobalObjects::allCheckpoints[0]);
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
    int deltaDenom = GlobalConstants::deltaDenom;
    unsigned long long now = SDL_GetPerformanceCounter();
    unsigned long long last = 0;
    double deltaTime = 0;

    while(!quit && !menu.exitGame) {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last)*1000 / (double)SDL_GetPerformanceFrequency() );

        // If the game is paused, no input shall be accepted, except for quit (escape) and unpause (p)
        if (pause) {
            determineInput(1);
            render();
            continue;
        }

        // Merge with pause check
        if (!menu.startGame || menu.pause) {
            determineInput(1);
            handleMenu();
            render();
            continue;
        }

        //processInput(deltaTime);
        player.velocity.x *= 0.8;
        auto move = determineInput(deltaTime/deltaDenom);
        if(quit){
            break;
        }

        player.velocity += move;
        player.upkeep(deltaTime/deltaDenom);

        nonPlayerUpkeep(deltaTime/deltaDenom);

        if(player.vit.hp <= 0){
            std::cout << "GIT GUD" << std::endl;
            GlobalObjects::clear();
            room = utility::parseRoom(player.lastCP->room, *renderer, GlobalObjects::resolution);
            currentRoom = player.lastCP->room;
            fillGlobalObjects(room, false);
            bossFight = false;
            player.kill();
        }
        //todo fix this shit
        if(!bossFight && room.roomId == 3 && !bossDefeated(1)) {

            bossFight = true;
            GlobalObjects::musicPlayer.play(BOSS, 0);
            spawnBoss(800, 800);
        }

        if(scuff3 && GlobalObjects::bosses.size() == 0){
            Mix_PlayMusic(gMusicVic, 1);
            scuff3 = false;
        }

        //TODO make enemies respawn & only activate cps when prompted
        for(auto& c: GlobalObjects::roomCheckpoints){
                if (utility::hitboxCollision(player.hitbox, player.position, c->hitbox, c->position)) {
                    player.rest();
                    player.lastCP = c;
                    if(GlobalObjects::savedVariables.currentCheckpoint != c->id){
                        GlobalObjects::savedVariables.currentCheckpoint = c->id;
                        GlobalObjects::savedVariables.serialize();
                    }
                }
        }

        render();
        cleanup(scuff3);

    }
    return 0;
}

void Game::handleMenu() {
    //if (menu.saveGame && menu.pause) {  // Only has an effect mid-game
    if (menu.saveGame) {  // Only has an effect mid-game
        GlobalObjects::savedVariables.musicVolume = musicVolume;
        GlobalObjects::savedVariables.effectVolume = effectVolume;
        GlobalObjects::savedVariables.debugActive = menu.optionsMenu.debugActive;
        GlobalObjects::savedVariables.serialize();
        menu.saveGame = false;
    }

    // Options menu
    if (menu.inOptions) {
        if (menu.optionsMenu.increaseMusicVolume) {
            if (getMusicVolume() <= 108)
                musicVolume++;
            menu.optionsMenu.increaseMusicVolume = false;
        }
        else if (menu.optionsMenu.decreaseMusicVolume) {
            if (getMusicVolume() >= 12)
                musicVolume--;
            menu.optionsMenu.decreaseMusicVolume = false;
        }
        else if (menu.optionsMenu.increaseEffectVolume) {
            if (getEffectVolume() <= 108)
                effectVolume++;
            menu.optionsMenu.increaseEffectVolume = false;
        }
        else if (menu.optionsMenu.decreaseEffectVolume) {
            if (getEffectVolume() >= 12)
                effectVolume--;
            menu.optionsMenu.decreaseEffectVolume = false;
        }

        Mix_VolumeMusic(getMusicVolume());
        //Mix_Volume(-1, getVolume());
        Mix_Volume(-1, getEffectVolume());
    }
}

vec_t Game::determineInput(double delta){

    // First check escape and 'p' in case the game is paused
    quit = !inputManager.update();

    if(inputManager.isPressed(KEY_ESCAPE)){
        if (player.canPause()) {
            player.pause();

            if (menu.inOptions)
                menu.inOptions = !menu.inOptions;
            else
                menu.pause = !menu.pause;
        }
    }

    if(inputManager.isPressed(KEY_O)){
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
    if(inputManager.isPressed(KEY_S)) {
        // player.velocity = {0, 0};    // Makes the player hover lol
        if(player.vit.stam > 0){
            player.velocity.y *= 0.2;
            player.vit.stam -= delta * player.staminaCostReduction * player.floatStaminaCost;
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
    /*
    if(inputManager.isPressed(KEY_F)){//cp
    }
     */
    if(inputManager.isPressed(KEY_Q)){//test
        if(GlobalObjects::telegraphedAttacks.size() == 0){
            TelegraphedAttack ta;
            ta.maxTime = 10;
            ta.damage = 10;
            ta.set(player.position.x-50, player.position.y, 100, 50);
            GlobalObjects::telegraphedAttacks.push_back(ta);
        }
    }
    if(inputManager.isPressed(KEY_V)){
        player.position={50, 50};
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (!menu.startGame || menu.pause) {
        menu.resolveMouseInput(mouseX, mouseY, false);
    }

    if (inputManager.isMousePressed(MOUSE_LEFT)) {
        if ((!menu.startGame || menu.pause)) {
            menu.resolveMouseInput(mouseX, mouseY, true);
        }
    }
    if (inputManager.isMouseHeld(MOUSE_LEFT) || inputManager.isMousePressed(MOUSE_LEFT)){
        if (menu.startGame  && !menu.pause) {
            GlobalObjects::abilities[0].useIfAvail(delta, player.position);
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

    if(inputManager.keyDown[KEY_LEFT_SHIFT]){
        player.dashingDown = true;
    }
    if(inputManager.keyUp[KEY_LEFT_SHIFT]){
        player.dashingDown = false;

        if(player.vit.stam >= 0) {
            player.dashingUp = true;
            vec_t playerMiddle = player.getMiddle();
            vec_t playerToMouse = inputManager.mouseVec() - playerMiddle;
            double length = playerToMouse.length();
            playerToMouse.normalize();
            playerToMouse *= std::min(player.dashRange, length);
            vec_t tmp = playerToMouse + playerMiddle;

            player.dashTo(tmp);
        }
    }

    // Check mouse position for button highlighting.


    return{out.x, out.y};
}

void Game::render() {
    // Clear the renderer and print the background.
    renderer->renderColor(255, 255, 255, 0);
    renderer->clear();

    // Menu
    if (!menu.startGame) {
        menu.renderMenu(*renderer);
        renderer->render();
        return;
    }

    // Room
    room.render(*renderer);

    // Render pause screen
    if (pause)
        pauseImage.render(*renderer);

    player.inventory.renderInventory();

    /// Render debug stuff ///
    if (menu.optionsMenu.debugActive)
        renderDebugTextures();

    // Render the player after the background
    //renderer->renderTriangles(player.hitbox, 255, 0, 0, player.position);
    player.render(*renderer);

    for (auto& projectile : GlobalObjects::projectiles) {
        //renderer->renderTexture(projectile.imageNew.getTexture(), nullptr, projectile.rec.get());
        //renderer->renderTriangles(projectile->hitbox, 255, 255, 255, projectile->position);
    }

    for (auto& p : GlobalObjects::platforms){
        std::vector<triangle> t = {p->top, p->bot};
        //renderer->renderTriangles(t, 0, 0, 0, {0,0});
    }
    for (auto& e : GlobalObjects::enemies){
        //renderer->renderTriangles(e->hitbox,255, 255, 0,e->position);
    }
    for (auto& g : GlobalObjects::gates){
        //renderer->renderTriangles(g->hitbox, 0,255, 255, g->position);
    }
    for (auto& b : GlobalObjects::bosses){
        scuff2 = true;
        //renderer->renderTriangles(b->hitbox, 255, 0, 255, b->position);
        b->bars[0].renderBar(*renderer);
        //b.healthBar.renderBar(*renderer);
    }
    for(auto& c : GlobalObjects::allCheckpoints){
        if(boost::algorithm::equals(currentRoom, c.room)) {
            if (player.lastCP->id == c.id) {
                //renderer->renderTriangles(c.hitbox, 0, 255, 0, c.position);
                renderer->renderTexture(c.texture, nullptr, &c.rectangle);
            } else {
                //renderer->renderTriangles(c.hitbox, 0, 120, 0, c.position);
                renderer->renderTexture(c.texture, nullptr, &c.rectangle);
            }
        }
    }
    for(auto& i : GlobalObjects::enemies) {
        i->render(*renderer);
    }
    for(auto& i : GlobalObjects::projectiles) {
        i->render(*renderer);
    }

    for(auto& i: GlobalObjects::telegraphedAttacks){
        i.render(*renderer);
    }

    player.healthBar.renderBar(*renderer);
    player.staminaBar.renderBar(*renderer);


    /// Status effects ///
    if (player.vit.bleed > 0)
        player.bleedBar.renderBar(*renderer);
    else if (player.vit.bleeding)
        player.activeBleedBar.renderBar(*renderer);

    if (player.vit.shock > 0)
        player.shockBar.renderBar(*renderer);
    else if (player.vit.shocked)
        player.activeShockBar.renderBar(*renderer);

    /// Pause menu ///
    if (menu.pause)
        menu.renderMenu(*renderer);

    /// Dash Range ///

    if(player.dashingDown){
        drawDashHelper();
    }

    renderer->render();
}

void Game::renderDebugTextures() {
    renderer->renderTriangles(player.hitbox, 255, 0, 0, player.position);

    for (auto& projectile : GlobalObjects::projectiles) {
        renderer->renderTriangles(projectile->hitbox, 255, 255, 255, projectile->position);
    }
    for (auto& p : GlobalObjects::platforms){
        std::vector<triangle> t = {p->top, p->bot};
        renderer->renderTriangles(t, 0, 0, 0, {0,0});
    }
    for (auto& e : GlobalObjects::enemies){
        renderer->renderTriangles(e->hitbox,255, 255, 0,e->position);
    }
    for (auto& g : GlobalObjects::gates){
        renderer->renderTriangles(g->hitbox, 0,255, 255, g->position);
    }
    for (auto& b : GlobalObjects::bosses){
        renderer->renderTriangles(b->hitbox, 255, 0, 255, b->position);
    }
    for(auto& c : GlobalObjects::allCheckpoints){
        if(boost::algorithm::equals(currentRoom, c.room)) {
            if (player.lastCP->id == c.id) {
                renderer->renderTriangles(c.hitbox, 0, 255, 0, c.position);
            } else {
                renderer->renderTriangles(c.hitbox, 0, 120, 0, c.position);
            }
        }
    }
    for(auto& i : GlobalObjects::enemies) {
        //i->render(*renderer);
    }
    for(auto& i : GlobalObjects::projectiles) {
        //i->render(*renderer);
    }
    for(auto& i: GlobalObjects::telegraphedAttacks){
        //i.render(*renderer);
    }
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
}
void Game::cleanup(bool& remove){
    std::vector<TelegraphedAttack> tas;
    {
        auto it = GlobalObjects::telegraphedAttacks.begin();
        while (it != GlobalObjects::telegraphedAttacks.end()) {

            if ((it->time < it->maxTime)) {
                tas.push_back(*it);
            } else{
                it->fire();
            }
            ++it;
        }
    }
    std::vector<std::shared_ptr<Projectile>> ps;
    {
        auto it = GlobalObjects::projectiles.begin();
        while (it != GlobalObjects::projectiles.end()) {

            if (it->get()->alive) {
                ps.push_back(*it);
            }
            ++it;
        }
    }
    std::vector<std::shared_ptr<Enemy>> es;
    {
        auto it = GlobalObjects::enemies.begin();
        while (it != GlobalObjects::enemies.end()) {

            if (it->get()->health <= 0) {
                it->get()->kill();
            } else {
                es.push_back(*it);
            }
            ++it;
        }
    }
    std::vector<std::shared_ptr<Boss>> bs;
    {
        auto it = GlobalObjects::bosses.begin();
        while (it != GlobalObjects::bosses.end()) {

            if (!it->get()->defeated) {
                bs.push_back(*it);
            } else{
                std::cout << "YOU DEFEATED" << std::endl;
            }
            ++it;
        }
    }


    GlobalObjects::telegraphedAttacks = tas;
    GlobalObjects::enemies = es;
    GlobalObjects::projectiles = ps;
    GlobalObjects::bosses = bs;
}
void Game::fillGlobalObjects(Room &room, bool initial) {
    if(!initial) {
        GlobalObjects::musicPlayer.initialId = room.musicId;
        GlobalObjects::musicPlayer.initialType = AREAS;
        GlobalObjects::musicPlayer.play(AREAS, room.musicId);
    } else{
        GlobalObjects::musicPlayer.play(OTHER, 0);
    }
    room.fillPlatformVector(GlobalObjects::platforms);
    room.fillEnemyVector(GlobalObjects::enemies);
    for(auto i : GlobalObjects::enemies) {
        i.get()->init(*renderer);
    }
    room.fillDoorVector(GlobalObjects::gates);
    GlobalObjects::roomCheckpoints.clear();
    for(auto& c : GlobalObjects::allCheckpoints){
        if(boost::algorithm::equals(c.room, currentRoom)) {
            GlobalObjects::roomCheckpoints.push_back(&c);
        }
    }
}

void Game::spawnBoss(int x, int y){

    BossBuilder::buildBoss( 1, {20,20});
}

bool Game::bossDefeated(int i){
    int tmp = GlobalObjects::savedVariables.bossesDefeated >> (i - 1);
    GlobalObjects::musicPlayer.play(AREAS, room.musicId);
    return tmp & 1;
}

void Game::loadSavedVariables(){
    std::ifstream file("savegame.txt");
    if(file.good()) {
        GlobalObjects::savedVariables.deSerialize(file);
    }
    file.close();
    makeCheckpoints();
    for(auto& c: GlobalObjects::allCheckpoints){
        if(GlobalObjects::savedVariables.currentCheckpoint == c.id){
            player.position = c.position;
            currentRoom = c.room;
        }
    }
    Ability a;
    AbilityPicker<Ability> ap;
    ap.pickAbility(a, GlobalObjects::savedVariables.rangedWeapon, PL_RANGED);
    GlobalObjects::abilities.push_back(a);
    ap.pickAbility(a, GlobalObjects::savedVariables.meleeWeapon, PL_MELEE);
    GlobalObjects::abilities.push_back(a);

    musicVolume = GlobalObjects::savedVariables.musicVolume;
    effectVolume = GlobalObjects::savedVariables.effectVolume;

}

void Game::nonPlayerUpkeep(double deltaTime){
    for(auto& e : GlobalObjects::enemies){
        e->upkeep(deltaTime);
        if (!e->damageOnTouch == 0){
            if(utility::hitboxCollision(player.hitbox, player.position, e->hitbox, e->position)){
                player.getHit(e->damageOnTouch);
            }
        }

    }
    for (auto& projectile : GlobalObjects::projectiles) {
        projectile->textureLocation = "files/textures/weapons/projectile_01.png";
        projectile->upkeep(deltaTime);
        if(projectile->owner == HOSTILE) {
            if (projectile->collide(player)) {
                projectile->resolve(player);
            }
        }else if (projectile->owner == PLAYER){
            for (auto& e : GlobalObjects::enemies) {
                if (projectile->collide(*e)) {
                    e->getHit(projectile->damage);
                    projectile->alive = false;
                }
            }
            for (auto& b: GlobalObjects::bosses) {
                if (projectile->collide(*b, false)) {
                    b->getHit(projectile->damage);
                    projectile->alive = false;
                }
            }
        }
        if(projectile->fragile){
            for(auto& platform: GlobalObjects::platforms){
                for(auto& tri: projectile->hitbox){
                    triangle tmp = tri;
                    tmp += projectile->position;
                    if(platform->collide(tmp)){
                        projectile->alive = false;
                    }
                }
            }
        }
    }
    for(auto& boss : GlobalObjects::bosses){
        boss->upkeep(deltaTime);
    }
    bool leave = false;
    for(auto& gate : GlobalObjects::gates){
        for(triangle t : player.hitbox) {
            t+=player.position;
            if (gate->collide(t)) {

                currentRoom = gate->nextRoomPath;
                std::cout << "moving to " << currentRoom << std::endl;
                player.position = gate->newPosition;
                GlobalObjects::clear();
                room = utility::parseRoom(currentRoom, *renderer, GlobalObjects::resolution);
                fillGlobalObjects(room, false);
                leave = true;
                break;
            }

        }
        if(leave){
            break;
        }
    }

    for(auto& tas : GlobalObjects::telegraphedAttacks){
        tas.update(deltaTime);
    }
}

void Game::engageBoss(int id){

}
void Game::initializeMusic(){
    GlobalObjects::musicPlayer.load(AREAS, "Hades - Scourge of the Furies 1.mp3");
    GlobalObjects::musicPlayer.load(BOSS, "Hades - Scourge of the Furies 2.mp3");
    GlobalObjects::musicPlayer.load(OTHER, "Dead Cells OST - Title Menu.mp3");
    //gMusicVic=Mix_LoadMUS("files/music/Victory.mp3");

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

void Game::drawDashHelper(){
    int r = 255;
    int b = 255;
    int g = 255;
    int a = 255;
    if(player.vit.stam <= 0){
        b = 0;
        g = 0;
    }
    vec_t playerMiddle = player.getMiddle();
    circleRGBA(renderer->getRenderer(), playerMiddle.x, playerMiddle.y, player.dashRange, r, g, b, a);
    vec_t playerToMouse = inputManager.mouseVec() - playerMiddle;
    double length = playerToMouse.length();
    playerToMouse.normalize();
    playerToMouse *= std::min(player.dashRange, length);
    vec_t tmp = playerToMouse + playerMiddle;
    SDL_RenderDrawLine(renderer->getRenderer(), playerMiddle.x, playerMiddle.y, tmp.x, tmp.y);
}
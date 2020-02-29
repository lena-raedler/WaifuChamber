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
#include "utils/LingeringText.hpp"
#include "world/Message.hpp"
#include "entities/player/Pickup.hpp"

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
    std::vector<LingeringText> texts;
    std::vector<Message> messages;
    std::vector<std::shared_ptr<Pickup>> pickups;
    std::vector<LockedWall> lockedWalls;
    MusicPlayer musicPlayer;
    std::shared_ptr<Popup> popup;
    void clear(){
        enemies.clear();
        platforms.clear();
        projectiles.clear();
        gates.clear();
        bosses.clear();
        messages.clear();
        pickups.clear();
        texts.clear();
        telegraphedAttacks.clear();
        lockedWalls.clear();
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


    /// SDL_TTF ///
    //Initialize SDL_ttf

    //bool ttfSuccess;
    if (TTF_Init() == -1) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        //ttfSuccess = false;
    }

    //Text testText = Text();
    // Text::Text(std::string text, std::string fontPath, int fontSize, SDL_Color messageColor)
    //testText = Text("Hello, I am a sample text :)", "files/freefont-20120503/FreeSerif.ttf", 40, {0, 0, 0});
    //testText = Text("Yo guys, what's up?", 80, {0x88, 0x88, 0x88});
    //loadMedia();
    //testText.changeText("I am a different text now");
    /// END ///


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
    insertMessages();
    room.visited = true;
    fillGlobalObjects(room, true);

    // Map
    map.startPixels.x = GlobalObjects::resolution.first/2;
    map.startPixels.y = GlobalObjects::resolution.second/2;
    map.currentPosition = room.position;
    map.addTile(room.position);
    map.init();

    pauseImage = utility::loadImage("files/backgrounds/pauseTransparent.png", *renderer);

    quit = false;
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

    // Popup for upgrades
    GlobalObjects::popup = std::make_shared<Popup>();
    *GlobalObjects::popup = Popup("I am a popup :)");
    GlobalObjects::popup->text.rect.x = GlobalObjects::resolution.first/2 - GlobalObjects::popup->text.rect.w/2;
    GlobalObjects::popup->text.rect.y = GlobalObjects::resolution.second/2 - GlobalObjects::popup->text.rect.h/2;
}
void Game::makeCheckpoints(){
    SDL_Surface* s = IMG_Load("files/textures/savepoint_01.png");
    {

        Checkpoint c;
        if(!c.texture) {
            std::cerr << SDL_GetError() << std::endl;
        }
        c.position = utility::convert({3, 32});
        utility::fillDefaultHitbox(c.hitbox);
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({55, 30});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/dungeon1.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({40, 7});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/forest1.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({4, 24});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/dungeon5.txt";
        c.id = GlobalObjects::allCheckpoints.size();
        c.texture = renderer->createTextureFromSurface(s);
        c.rectangle = {(int)c.position.x, (int)c.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
        GlobalObjects::allCheckpoints.push_back(c);
    }
    {
        Checkpoint c;
        c.position = utility::convert({30, 4});
        utility::fillDefaultHitbox(c.hitbox);
        c.room = "files/rooms/tower3.txt";
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

    TTF_CloseFont( gFont );
    TTF_Quit();
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
        if (pause || map.inMap) {
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



        if(!skipMovement) {
            player.velocity += move;
            player.upkeep(deltaTime / deltaDenom);
        }

        bool atCp = false;
        for(auto& c: GlobalObjects::roomCheckpoints){
            if (utility::hitboxCollision(player.hitbox, player.position, c->hitbox, c->position)) {
                LingeringText t;
                t.text.changeText("Checkpoint");
                t.duration = 1;
                t.id = 11;
                t.text.rect = {static_cast<int>(player.position.x - 50), static_cast<int>(player.position.y - 40)};
                t.text.changeFontSize(20);
                t.print();
                player.rest();
                player.lastCP = c;
                atCp = true;
                if(GlobalObjects::savedVariables.currentCheckpoint != c->id){
                    GlobalObjects::savedVariables.currentCheckpoint = c->id;
                    GlobalObjects::savedVariables.serialize();
                }
            }
        }

        if(atCp){
            GlobalObjects::projectiles.clear();
            skipMovement = false;
        }
        else {
            nonPlayerUpkeep(deltaTime / deltaDenom);
        }

        if(player.vit.hp <= 0){
            std::cout << "GIT GUD" << std::endl;
            GlobalObjects::clear();
            room = utility::parseRoom(player.lastCP->room, *renderer, GlobalObjects::resolution);
            currentRoom = player.lastCP->room;
            fillGlobalObjects(room, false);
            bossFight = false;
            player.kill();
        }
        /*
        //todo fix this shit
        if(!bossFight && room.roomId == 3 && !bossDefeated(1)) {

            bossFight = true;
            GlobalObjects::musicPlayer.play(BOSS, 0);
            spawnBoss(800, 800);
        }
*/

        // check for levelUp
        if(GlobalObjects::savedVariables.souls >= 4500 && player.level < 5) {
            utility::displayMessage("Level Up!", player.position, 7, 14335);
            player.levelUp();
            GlobalObjects::savedVariables.level += 1;
            GlobalObjects::savedVariables.souls -= 4500;
            GlobalObjects::savedVariables.serialize();

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
    // TODO The optionsMen.boolSomething doesn't need to get set to false; I can do this within the Button itself
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
        else if (menu.optionsMenu.returnButton.clicked) {
            menu.inOptions = !menu.inOptions;
            menu.optionsMenu.returnButton.clicked = false;
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
    if(inputManager.isPressed(KEY_E)){
        /* Interact with stuff*/
        for(auto& p : GlobalObjects::pickups){
            if(utility::hitboxCollision(player.hitbox, player.position, p->m.hitbox, p->m.position)){
                player.addPickup(*p);
                p->pFunction();
            }
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

    // Map
    if (inputManager.isPressed(KEY_M)) {
        if (player.canPause()) {
            player.pause();
            map.inMap = !map.inMap;
            if (map.inMap) {
                std::cout << "Show map" << std::endl;
                map.currentPosition = room.position;
                //map.updateCurrentTile();
            }
            else {
                std::cout << "Hide map" << std::endl;
            }
        }
    }

    vec_t out{0, 0};

    // If the game is paused ignore all other input
    if (pause)
        return out;

    if (map.inMap)
        return out;

    // check which buttons were pressed
    if(inputManager.isPressed(KEY_A)) {
        out.x += -speed;}
    if(inputManager.isPressed(KEY_D)) {
        out.x += speed;}
    if(inputManager.keyDown[KEY_W] || inputManager.keyDown[KEY_SPACE]) {
        if (player.canJump()) {
            player.jump();
        }
    }
    if(inputManager.isPressed(KEY_S) && utility::decode(GlobalObjects::savedVariables.upgrades,0)) {
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

    if(inputManager.keyDown[KEY_LEFT_SHIFT] && utility::decode(GlobalObjects::savedVariables.upgrades, 2)){
        player.dashingDown = true;
    }
    if(inputManager.keyUp[KEY_LEFT_SHIFT] && utility::decode(GlobalObjects::savedVariables.upgrades, 2)){
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
    //renderer->renderTriangles(player.hitboxOpen, 255, 0, 0, player.position);
    player.render(*renderer);

    for (auto& projectile : GlobalObjects::projectiles) {
        projectile.get()->render(*renderer);
        //renderer->renderTexture(projectile.imageNew.getTexture(), nullptr, projectile.rec.get());
        //renderer->renderTriangles(projectile->hitboxOpen, 255, 255, 255, projectile->position);
    }

    for (auto& p : GlobalObjects::platforms){
        std::vector<triangle> t = {p->top, p->bot};
        //renderer->renderTriangles(t, 0, 0, 0, {0,0});
    }
    /*
    for (auto& e : GlobalObjects::enemies){
        //renderer->renderTriangles(e->hitboxOpen,255, 255, 0,e->position);
    }
    for (auto& g : GlobalObjects::gates){
        //renderer->renderTriangles(g->hitboxOpen, 0,255, 255, g->position);
    } */
    for (auto& b : GlobalObjects::bosses){
        scuff2 = true;
        //renderer->renderTriangles(b->hitboxOpen, 255, 0, 255, b->position);
        b->bars[0].renderBar(*renderer);
        //b.healthBar.renderBar(*renderer);
        b->nameText.render();
        b->render(*renderer);
    }
    for(auto& c : GlobalObjects::allCheckpoints){
        if(boost::algorithm::equals(currentRoom, c.room)) {
            if (player.lastCP->id == c.id) {
                //renderer->renderTriangles(c.hitboxOpen, 0, 255, 0, c.position);
                renderer->renderTexture(c.texture, nullptr, &c.rectangle);
            } else {
                //renderer->renderTriangles(c.hitboxOpen, 0, 120, 0, c.position);
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

    for(auto& lt: GlobalObjects::texts){
        lt.text.render();
    }
    for(auto& lt: GlobalObjects::pickups){
        lt->m.render(*GlobalObjects::renderPtr);
    }
    //testText.render();
    //renderTTF( (1920-mWidth)/2, (1080-mHeight)/2 );
    //SDL_RenderCopyEx( *renderer, mTexture, clip, &renderQuad, angle, center, flip );

    // Popup
    GlobalObjects::popup->displayPopup();

    // Map
    if (map.inMap) {
        map.render();
        //renderer->render();
        //return;
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
    for (auto& b : GlobalObjects::pickups){
        renderer->renderTriangles(b->m.hitbox, 255, 120, 255, b->m.position);
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
    for(auto& m : GlobalObjects::messages){
        renderer->renderTriangles(m.m.hitbox, 255, 50, 120, m.m.position);
    }
    //for(auto& i : GlobalObjects::enemies) {
        //i->render(*renderer);
    //}
    //for(auto& i : GlobalObjects::projectiles) {
        //i->render(*renderer);
    //}
    //for(auto& i: GlobalObjects::telegraphedAttacks){
        //i.render(*renderer);
    //}
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
                GlobalObjects::musicPlayer.play(AREAS, room.musicId);
                std::cout << "YOU DEFEATED" << std::endl;
            }
            ++it;
        }
    }
    {
        auto it = GlobalObjects::texts.begin();
        while (it != GlobalObjects::texts.end()) {

            if ((it->duration > 0)) {
                ++it;
            } else{
                it = GlobalObjects::texts.erase(it);
            }
        }
    }
    {
        auto it = GlobalObjects::pickups.begin();
        while (it != GlobalObjects::pickups.end()) {

            if ((!player.hasPickup(it->get()->id))) {
                ++it;
            } else{
                it = GlobalObjects::pickups.erase(it);
            }
        }
    }
    {
        auto it = GlobalObjects::lockedWalls.begin();
        while (it != GlobalObjects::lockedWalls.end()) {

            if (it->closed) {
                ++it;
            } else{
                it = GlobalObjects::lockedWalls.erase(it);
            }
        }
    }
    //std::cout << GlobalObjects::lockedWalls.size() << std::endl;


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
    for(auto& i : GlobalObjects::enemies) {
        i.get()->init(*renderer);
    }
    room.fillBossVector(GlobalObjects::bosses);
    if(GlobalObjects::bosses.size() > 0){
        GlobalObjects::musicPlayer.play(BOSS, GlobalObjects::bosses[0]->id - 1);
    }
    for(auto& i : GlobalObjects::bosses) {
        i.get()->init(*renderer);
    }
    room.fillDoorVector(GlobalObjects::gates);
    GlobalObjects::roomCheckpoints.clear();
    for(auto& c : GlobalObjects::allCheckpoints){
        if(boost::algorithm::equals(c.room, currentRoom)) {
            GlobalObjects::roomCheckpoints.push_back(&c);
        }
    }
    for(auto& p :room.pickupItems){

        Pickup pu;
        pu.m.textureLocation = "files/texures/weapons/projectile01.png";
        utility::fillDefaultHitbox(pu.m.hitbox);
        pu.m.init();
        pu.m.gravityType = NORMAL;
        if(!utility::decode(GlobalObjects::savedVariables.pickups, p.id)){
            pu.id = p.id;
            pu.m.position = {static_cast<double>(p.position.x), static_cast<double>(p.position.y)};
            pu.setFunction();
            GlobalObjects::pickups.push_back(std::make_shared<Pickup>(pu));
        }
    }
    for(auto& lw: room.lockedWalls){
        lw.id = room.roomId;
        std::cout << "ID:" << lw.id << std::endl;
        if(!utility::decode(GlobalObjects::savedVariables.oneways, lw.id)){
            lw.init();
            GlobalObjects::lockedWalls.push_back(lw);
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
    player.level = GlobalObjects::savedVariables.level;
    player.vit.maxHp = 90 + 10*player.level;
    player.vit.maxStam = 90 + 10*player.level;
    GlobalObjects::abilities[0].projectiles[0].damage = (18 + 2*player.level);
    std::cout << "level: " << player.level << std::endl;

}

void Game::nonPlayerUpkeep(double deltaTime){
    for(auto& e : GlobalObjects::enemies){
        e->upkeep(deltaTime);
        if (!e->damageOnTouch == 0){
            if(utility::hitboxCollision(player.hitbox, player.position, e->hitbox, e->position)){
                player.getHit(e->damageOnTouch);
                statuseffect s = e->statusOnTouch;
                switch (s.type) {
                    case BLEED:
                        if(!player.vit.bleeding) {
                            player.vit.bleed += s.intensity;
                        }
                        break;
                    case SHOCK:
                        if(!player.vit.shocked) {
                            player.vit.shock += s.intensity;
                        }
                        break;
                    case BURN:
                        if(!player.vit.burning) {
                            player.vit.burn += s.intensity;
                        }
                        break;
                    case ROT:
                        if(!player.vit.rotting) {
                            player.vit.rot += s.intensity;
                        }
                        break;
                    case FRENZY:
                        if(!player.vit.frenzied) {
                            player.vit.frenzy += s.intensity;
                        }
                        break;
                    default:
                        break;
                }
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
    skipMovement = false;
    for(auto& gate : GlobalObjects::gates){
        for(triangle t : player.hitbox) {
            t+=player.position;
            if (gate->collide(t)) {
                if(player.hasKey(*gate)){
                    currentRoom = gate->nextRoomPath;
                    std::cout << "moving to " << currentRoom << std::endl;
                    player.position = gate->newPosition;
                    GlobalObjects::clear();
                    int oldMusic = room.musicId;
                    skipMovement = true;
                    player.velocity ={0,0};
                    room = utility::parseRoom(currentRoom, *renderer, GlobalObjects::resolution);
                    room.visited = true;
                    map.currentPosition = room.position;
                    map.addTile(room.position);
                    if(room.musicId == -1){
                        room.musicId = oldMusic;
                    }
                    insertMessages();
                    fillGlobalObjects(room, false);
                    leave = true;
                    break;

                }
                else{
                    LingeringText t;
                    t.text.changeText("Locked");
                    t.duration = 1;
                    t.id = 11;
                    t.text.rect = {static_cast<int>(player.position.x - 50), static_cast<int>(player.position.y - 40)};
                    t.text.changeFontSize(20);
                    t.print();
                }


            }

        }
        if(leave){
            break;
        }
    }

    for(auto& tas : GlobalObjects::telegraphedAttacks){
        tas.update(deltaTime);
    }
    for(auto& m: GlobalObjects::messages){
        if(utility::hitboxCollision(player.hitbox, player.position, m.m.hitbox, m.m.position)){
            m.print();
        }
    }

    for(auto& lw : GlobalObjects::lockedWalls){
        if(utility::hitboxCollision(player.hitbox, player.position, lw.hitboxOpen, lw.pos_double)){
            lw.unlock(player.position);
            room.removeLockedWall(lw);
        }

    }

    for(auto& lt : GlobalObjects::texts){
        lt.upkeep(deltaTime);
    }
}

void Game::engageBoss(int id){

}
void Game::initializeMusic(){
    GlobalObjects::musicPlayer.load(AREAS, "Hades - Scourge of the Furies 1.mp3");
    GlobalObjects::musicPlayer.load(BOSS, "Hades - Scourge of the Furies 2.mp3");
    GlobalObjects::musicPlayer.load(BOSS, "Pyre Original Soundtrack - Night Howlers.mp3");

    GlobalObjects::musicPlayer.load(BOSS, "Pyre Original Soundtrack - Will of the Scribes.mp3");
    GlobalObjects::musicPlayer.load(OTHER, "Dead Cells OST - Title Menu.mp3");
    GlobalObjects::musicPlayer.load(BOSS, "Boss Boss Boss - Katana ZERO.mp3");
    GlobalObjects::musicPlayer.load(AREAS, "Dead Cells OST - The Promenade.mp3");
    GlobalObjects::musicPlayer.load(AREAS, "Dead Cells - ClockTower (Official Soundtrack).mp3");
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


bool Game::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
    //Get rid of preexisting texture
    //free();
    if (mTexture != nullptr) {
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer->getRenderer(), textSurface );
        if( mTexture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != nullptr;
}

bool Game::loadMedia() {
    //Loading success flag
    bool success = true;

    //Open the font
    //gFont = TTF_OpenFont( "16_true_type_fonts/lazy.ttf", 28 );
    //gFont = TTF_OpenFont( "/home/bnorb/CLionProjects/WaifuChamber/exercises/test/lazy.ttf", 28 );
    gFont = TTF_OpenFont( "files/freefont-20120503/FreeSerif.ttf", 40 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !loadFromRenderedText( "Fuck you CMake DansGame", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    return success;
}

void Game::renderTTF( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( renderer->getRenderer(), mTexture, clip, &renderQuad, angle, center, flip );
}
void Game::insertMessages(){
    Message m;
    switch(room.roomId){

        case 2:

            utility::fillDefaultHitbox(m.m.hitbox);
            m.m.position = utility::convert(4, 32);
            m.t.text.changeText("W/Space : Jump");
            m.t.id = 1001;
            m.t.duration = 20;
            GlobalObjects::messages.push_back(m);
            m.t.text.changeText("LMB : Shoot");
            m.t.id = 1002;
            m.m.position = utility::convert(51, 31);
            GlobalObjects::messages.push_back(m);
            break;
        case 5:
            m.t.text.changeText("E : Pick up Key");
            m.t.id = 1002;
            m.m.position = utility::convert(51, 31);
            GlobalObjects::messages.push_back(m);
            break;
        default:
            break;
    }
}
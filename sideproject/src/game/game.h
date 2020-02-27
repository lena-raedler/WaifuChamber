//
// Created by lena on 11/8/19.
//

#ifndef WAIFUCHAMBER_GAME_H
#define WAIFUCHAMBER_GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <string>
#include <memory>
#include "utils/Vec2.h"
#include "utils/renderer.h"
#include "entities/player/player.h"
#include "entities/player/Projectile.hpp"
#include "utils/InputManager.h"
#include <utility>
#include "utils/utility.h"
#include "world/room.h"
#include "utils/Image.h"
#include "SavedVariables.h"
#include <fstream>
#include "Inventory/Inventory.hpp"
#include "entities/player/Enemy.h"
#include "Inventory/Slot.hpp"
#include "entities/player/Ability.h"
#include "menu/Menu.hpp"
#include "utils/Text.hpp"
#include "./world/Map.hpp"

// QT Widget
//#include "Calculator/calculator.hpp"
//#include "menu/Menu.hpp"
//#include <QApplication>

class Game {
public:
    Game();
    ~Game();
    int loop();

private:

    void cleanup(bool& s);
    InputManager inputManager;

    bool bossDefeated(int i);
    void render();
    void updateHealthBar();
    void renderHealthBar();
    void processInput(double delta);
    vec_t determineInput(double delta);
    void renderInventory();
    void makeCheckpoints();
    void loadSavedVariables();
    //int renderInventory2(int argc, char *argv[]);
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Event e;
    SDL_Rect rectangle;
    std::shared_ptr<Renderer> renderer;
    bool quit;
    bool pause;
    Image pauseImage;
    SDL_Surface* surface;
    Player player;
    bool left;
    bool right;
    bool up;
    bool isFalling;
    const int speed = 10;
    vec_t playerPosition;
    int screenHeight = 1080;     // Original: 480
    int screenWidth = 1920; // Original: 640
    const int jumpHeight = 10;
    int jump = 0;
    void debugshit();//1st statement that is executed, do all kinds of testing in this
    SDL_Rect healthBarBorderRect;   // If this is defined after background then a SEGFAULT occurs(??)
    SDL_Rect healthBarBackgroundRect;
    SDL_Rect healthBarRect;

    std::string currentRoom; //filepath to the currently loaded room
    Room room;
    std::vector<Checkpoint> checkpoints;
    std::vector<Platform> platforms;
    //Inventory inventory;
    std::vector<Ability> abilities;
    Menu menu;
    Map map;
    Image healthBarImage;

    int effectVolume, musicVolume, volumeStep;
    int getEffectVolume() { return effectVolume * volumeStep; }
    int getMusicVolume() { return musicVolume * volumeStep; }
    void handleMenu();
    void renderDebugTextures();

    //Globally used font
    TTF_Font *gFont = nullptr;
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    bool loadMedia();

    //The actual hardware texture
    SDL_Texture* mTexture;
    int mWidth = 0;
    int mHeight = 0;
    void renderTTF( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Text testText;

    /////////////////////////////////DELETE THIS////////////////////////////////////////////////////////
    //this is just to quickly test things, everything below this will be removed
    std::vector<Projectile> projs;
    bool bossFight = false;
    bool scuff2 = false;
    bool scuff3 = false;

    void spawnBoss(int x, int y);
    void fillGlobalObjects(Room &room, bool initial);

    void nonPlayerUpkeep(double deltaTime);

    void engageBoss(int id);

    void initializeMusic();

    void drawDashHelper();

    void insertMessages();
};


#endif //WAIFUCHAMBER_GAME_H

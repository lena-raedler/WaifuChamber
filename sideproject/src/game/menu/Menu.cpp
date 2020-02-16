//
// Created by bnorb on 06.02.20.
//

#include "Menu.hpp"
#include "../GlobalObjects.h"
//#include "../game.h"


Menu::Menu(Renderer& renderer) {
    mainMenuImage = utility::loadImage("files/textures/menu/main_menu_background.png", renderer);
    pauseImage = utility::loadImage("files/textures/menu/pause_menu_background.png", renderer);
    pauseImage.getRect()->x = 1920 / 2 - pauseImage.getRect()->w / 2;   // Using GlobalObjects::resolution.first() gives me errors because platform is uninitialized(?)

    int width = 299;    // Exact size of the button textures
    int height = 84;
    int heightGap = 25;
    int x = 1920 / 2 - width / 2;
    int y = 1080 / 2 - height / 2 - height*2 - heightGap*2;
    startGameButton = Button(renderer, "files/textures/menu/start_game_2.png", "files/textures/menu/start_game_2_highlighted.png", "menu/GAMESTART.wav", MIX_MAX_VOLUME*3/4, x, y, width, height);
    continueGameButton = Button(renderer, "files/textures/menu/continue.png", "files/textures/menu/continue_highlighted.png", "menu/CURSOL_OK.wav", MIX_MAX_VOLUME*3/4, x, y, width, height);
    optionsGameButton = Button(renderer, "files/textures/menu/options_game.png", "files/textures/menu/options_game_highlighted.png", "menu/CURSOL_OK.wav", MIX_MAX_VOLUME*3/4, x, y + height + heightGap, width, height);
    saveGameButton = Button(renderer, "files/textures/menu/save_game.png", "files/textures/menu/save_game_highlighted.png","menu/CURSOL_OK.wav", MIX_MAX_VOLUME*3/4, x, y + (height+heightGap)*2, width, height);
    exitGameButton = Button(renderer, "files/textures/menu/exit_game_2.png", "files/textures/menu/exit_game_2_highlighted.png", "menu/CURSOL_CANCEL.wav", MIX_MAX_VOLUME*3/4, x, y + (height+heightGap)*3, width, height);
    startGame = false;
    exitGame = false;
    pause = false;
    optionsMenu = OptionsMenu(renderer);
}

void Menu::renderMenu(Renderer& renderer) {
    // Background
    if (!startGame)
        mainMenuImage.render(renderer);
    else
        pauseImage.render(renderer);

    // Buttons
    if (inOptions) {
        optionsMenu.renderOptionsMenu(renderer);
    } else {
        if (!startGame)
            startGameButton.renderButton(renderer);
        else
            continueGameButton.renderButton(renderer);

        optionsGameButton.renderButton(renderer);
        exitGameButton.renderButton(renderer);
        saveGameButton.renderButton(renderer);
    }

    startGameButton.highlighted = false;
    continueGameButton.highlighted = false;
    optionsGameButton.highlighted = false;
    exitGameButton.highlighted = false;
    saveGameButton.highlighted = false;
}

// TODO Make a sound when a button is pressed
void Menu::resolveMouseInput(int mouseX, int mouseY, bool clicked) {
    // Options menu
    if (inOptions) {
        optionsMenu.resolveMouseInput(mouseX, mouseY, clicked);
        return;
    }
    // Normal menu
    if (!startGame && !inOptions && startGameButton.inButton(mouseX, mouseY)) {
        startGameButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            startGame = true;
            pause = false;
            startGameButton.clicked = true;
            GlobalObjects::musicPlayer.playInitial();
        }
    }
    else if (startGame && !inOptions && continueGameButton.inButton(mouseX, mouseY)) {  // startGame check unnecessary, but still there for safety
        continueGameButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            startGame = true;
            pause = false;
            continueGameButton.clicked = true;
        }
    }
    else if (!inOptions && saveGameButton.inButton(mouseX, mouseY)) {
        saveGameButton.highlighted = true;
        if (clicked) {
            saveGame = true;
            saveGameButton.clicked = true;
        }
    }
    else if (!inOptions && optionsGameButton.inButton(mouseX, mouseY)) {
        optionsGameButton.highlighted = true;
        if (clicked) {
            inOptions = true;
            optionsGameButton.clicked = true;
        }
    }
    else if (exitGameButton.inButton(mouseX, mouseY)) {
        exitGameButton.highlighted = true;
        if (clicked) {
            exitGame = true;
            exitGameButton.clicked = true;
        }
    }
}
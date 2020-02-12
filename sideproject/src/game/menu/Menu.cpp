//
// Created by bnorb on 06.02.20.
//

#include "Menu.hpp"
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
    startGameButton = Button(renderer, "files/textures/menu/start_game_2.png", "files/textures/menu/start_game_2_highlighted.png", x, y, width, height);
    optionsGameButton = Button(renderer, "files/textures/menu/options_game.png", "files/textures/menu/options_game_highlighted.png", x, y + height + heightGap, width, height);
    saveGameButton = Button(renderer, "files/textures/menu/save_game.png", "files/textures/menu/save_game_highlighted.png", x, y + height*2 + heightGap*2, width, height);
    exitGameButton = Button(renderer, "files/textures/menu/exit_game_2.png", "files/textures/menu/exit_game_2_highlighted.png", x, y + height*3 + heightGap*3, width, height);
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
        startGameButton.renderButton(renderer);
        optionsGameButton.renderButton(renderer);
        exitGameButton.renderButton(renderer);
        saveGameButton.renderButton(renderer);
    }

    startGameButton.highlighted = false;
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
    if (!inOptions && startGameButton.inButton(mouseX, mouseY)) {
        startGameButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            startGame = true;
            pause = false;
            startGameButton.clicked = true;
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
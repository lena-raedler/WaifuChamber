//
// Created by bnorb on 06.02.20.
//

#include "Menu.hpp"
//#include "../game.h"


Menu::Menu(Renderer& renderer) {
    int width = 299;    // Exact size of the button textures
    int height = 84;
    int x = 1920 / 2 - width / 2;
    int y = 1080 / 2 - height / 2;
    startGameButton = Button(renderer, "files/textures/menu/start_game_2.png", "files/textures/menu/start_game_2_highlighted.png", x, y, width, height);
    exitGameButton = Button(renderer, "files/textures/menu/exit_game_2.png", "files/textures/menu/exit_game_2_highlighted.png", x, y + height + 25, width, height);
    startGame = false;
    exitGame = false;
    pause = false;
}

void Menu::renderMenu(Renderer& renderer) {
    startGameButton.renderButton(renderer);
    exitGameButton.renderButton(renderer);

    startGameButton.highlighted = false;
    exitGameButton.highlighted = false;
}

void Menu::resolveMouseInput(int mouseX, int mouseY, bool clicked) {
    if (startGameButton.inButton(mouseX, mouseY)) {
        startGameButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            startGame = true;
            pause = false;
        }
    }
    else if (exitGameButton.inButton(mouseX, mouseY)) {
        exitGameButton.highlighted = true;
        if (clicked)
            exitGame = true;
    }
}
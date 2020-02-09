//
// Created by bnorb on 06.02.20.
//

#include "Menu.hpp"
#include "../game.h"


Menu::Menu(Renderer& renderer) {
    int width = 299;    // Exact size of the button textures
    int height = 84;
    int x = 1920 / 2 - width / 2;
    int y = 1080 / 2 - height / 2;
    startGameButton = Button(renderer, "files/textures/menu/start_game_2_light.png", x, y, width, height);
    exitGameButton = Button(renderer, "files/textures/menu/exit_game_2_light.png", x, y + height + 25, width, height);
    startGame = false;
    exitGame = false;
}

void Menu::renderMenu(Renderer& renderer) {
    startGameButton.renderButton(renderer);
    exitGameButton.renderButton(renderer);
}

void Menu::resolveMouseInput(int mouseX, int mouseY) {
    if (startGameButton.inButton(mouseX, mouseY))
        startGame = true;
    else if (exitGameButton.inButton(mouseX, mouseY))
        exitGame = true;
}
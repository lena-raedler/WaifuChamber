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
    startGameButton = Button(renderer, "files/textures/menu/start_game_2.png", x, y, width, height);
    startGameButtonHighlighted = Button(renderer, "files/textures/menu/start_game_2_highlighted.png", x, y, width, height);
    currentStartGameButton = startGameButton;

    exitGameButton = Button(renderer, "files/textures/menu/exit_game_2.png", x, y + height + 25, width, height);
    exitGameButtonHighlighted = Button(renderer, "files/textures/menu/exit_game_2_highlighted.png", x, y + height + 25, width, height);
    currentExitGameButton = exitGameButton;
    startGame = false;
    exitGame = false;
    pause = false;
}

void Menu::renderMenu(Renderer& renderer) {
    currentStartGameButton.renderButton(renderer);
    currentExitGameButton.renderButton(renderer);

    currentStartGameButton = startGameButton;
    currentExitGameButton = exitGameButton;
}

void Menu::resolveMouseInput(int mouseX, int mouseY, bool clicked) {
    if (startGameButton.inButton(mouseX, mouseY)) {
        currentStartGameButton = startGameButtonHighlighted;
        if (clicked) {      // Unpause or start the game
            startGame = true;
            pause = false;
        }
    }
    else if (exitGameButton.inButton(mouseX, mouseY)) {
        currentExitGameButton = exitGameButtonHighlighted;
        if (clicked)
            exitGame = true;
    }
}
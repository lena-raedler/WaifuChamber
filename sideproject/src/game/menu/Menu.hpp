//
// Created by bnorb on 06.02.20.
//

#pragma once

#include "../utils/renderer.h"
#include "../utils/utility.h"
#include "Button.hpp"
#include "../utils/Image.hpp"

class Game;
class Menu {

public:
    Menu() = default;
    Menu(Renderer& renderer);
    ~Menu() = default;
    void renderMenu(Renderer& renderer);
    bool startGame, saveGame, optionsGame, exitGame, pause;
    Button startGameButton;
    Button optionsGameButton;
    Button exitGameButton;
    Button saveGameButton;
    Image mainMenuImage, pauseImage;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);

};
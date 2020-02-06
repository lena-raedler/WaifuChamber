//
// Created by bnorb on 06.02.20.
//

#pragma once

#include "../utils/renderer.h"
#include "../utils/utility.h"
#include "Button.hpp"

class Game;
class Menu {

public:
    Menu() = default;
    Menu(Renderer& renderer);
    ~Menu() = default;
    void renderMenu(Renderer& renderer);
    bool startGame, exitGame;
    Button startGameButton;
    Button exitGameButton;
    void resolveMouseInput(int mouseX, int mouseY);

};
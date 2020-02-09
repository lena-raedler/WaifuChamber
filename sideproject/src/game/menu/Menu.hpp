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
    bool startGame, saveGame, exitGame, pause;
    Button startGameButton;
    Button saveGameButton;
    Button exitGameButton;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);

};
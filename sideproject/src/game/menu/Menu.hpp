//
// Created by bnorb on 06.02.20.
//

#pragma once

#include "Button.hpp"
#include "OptionsMenu.hpp"
#include "../utils/Image.h"
#include "../utils/renderer.h"
#include "../utils/utility.h"
#include "../world/MusicPlayer.h"

class Game;
class Menu {

public:
    Menu() = default;
    Menu(Renderer& renderer);
    ~Menu() = default;
    bool startGame, saveGame, inOptions, exitGame, pause;
    Button startGameButton;
    Button optionsGameButton;
    Button exitGameButton;
    Button saveGameButton;
    Image mainMenuImage, pauseImage;
    OptionsMenu optionsMenu;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);
    void renderMenu(Renderer& renderer);

};
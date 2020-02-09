//
// Created by bnorb on 09.02.20.
//

#pragma once

#include "Button.hpp"
#include "../utils/Image.hpp"
#include "../utils/renderer.h"
#include "../utils/utility.h"

class OptionsMenu {

public:
    OptionsMenu() = default;
    OptionsMenu(Renderer& renderer);
    ~OptionsMenu() = default;
    Button increaseVolumeButton, decreaseVolumeButton;
    bool increaseVolume, decreaseVolume;
    Image volumeImage;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);
    void renderOptionsMenu(Renderer& renderer);
};


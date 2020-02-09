//
// Created by bnorb on 09.02.20.
//

#pragma once

#include "Button.hpp"
#include "../utils/Image.hpp"
#include "../utils/renderer.h"
#include "../utils/utility.h"
#include <string>
#include <vector>

class OptionsMenu {

public:
    OptionsMenu() = default;
    OptionsMenu(Renderer& renderer);
    ~OptionsMenu() = default;
    Button increaseVolumeButton, decreaseVolumeButton;
    bool increaseVolume, decreaseVolume;
    //Image volumeImage;
    std::vector<Image> volumeImages;    // TODO Initialize with size 10
    int volume;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);
    void renderOptionsMenu(Renderer& renderer);
};


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
    Button increaseEffectVolumeButton, decreaseEffectVolumeButton;
    bool increaseVolume, decreaseVolume;
    bool increaseEffectVolume, decreaseEffectVolume;
    std::vector<Image> volumeImages, effectVolumeImages;
    int volume;
    int effectVolume;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);
    void renderOptionsMenu(Renderer& renderer);
};


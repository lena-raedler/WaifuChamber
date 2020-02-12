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
    Button increaseEffectVolumeButton, decreaseEffectVolumeButton;
    Button increaseMusicVolumeButton, decreaseMusicVolumeButton;
    Button debugActiveButton, debugInactiveButton;
    bool increaseEffectVolume, decreaseEffectVolume;
    bool increaseMusicVolume, decreaseMusicVolume;
    bool debugActive;
    std::vector<Image> effectVolumeImages, musicVolumeImages;
    //std::vector<Image*> test;     // Maybe change musicVolumeImages to this, more efficient
    int effectVolume, musicVolume;
    void resolveMouseInput(int mouseX, int mouseY, bool clicked);
    void renderOptionsMenu(Renderer& renderer);
};


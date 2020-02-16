//
// Created by bnorb on 06.02.20.
//

#pragma once
#include "../utils/renderer.h"
#include "../utils/utility.h"
#include "../utils/Image.h"
#include "../GlobalConstants.h"
#include "../entities/player/SoundEffect.h"
#include <string>

class Button {

public:
    Button() = default;
    Button(Renderer& renderer, std::string imagePath, std::string imagePathHighlighted, int x, int y, int width, int height);
    Button(Renderer& renderer, std::string imagePath, std::string imagePathHighlighted, std::string soundPath, int soundVolume, int xTmp, int yTmp, int widthTmp, int heightTmp);
    ~Button() = default;
    int x, y, width, height = 0;
    Image image, imageHighlighted;
    bool highlighted, clicked;
    SoundEffect soundEffect;
    void renderButton(Renderer& renderer);
    bool inButton(int x2, int y2);
};

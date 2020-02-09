//
// Created by bnorb on 06.02.20.
//

#pragma once
#include "../utils/renderer.h"
#include "../utils/utility.h"
#include "../utils/Image.hpp"
#include "../GlobalConstants.h"
#include <string>

class Button {

public:
    Button() = default;
    Button(Renderer& renderer, std::string imagePath, std::string imagePathHighlighted, int x, int y, int width, int height);
    ~Button() = default;
    int x, y, width, height = 0;
    Image image, imageHighlighted;
    bool highlighted;
    void renderButton(Renderer& renderer);
    bool inButton(int x2, int y2);
};

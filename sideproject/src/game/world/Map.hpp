//
// Created by bnorb on 27.02.20.
//

#pragma once

#include <vector>
#include "../utils/Image.h"
#include "../utils/utility.h"
#include "../utils/Vec2.h"
#include "../GlobalObjects.h"
#include "../GlobalConstants.h"

class Map {
public:
    /// Constructor & Destructor ///
    Map();
    ~Map() = default;

    /// Fields ///
    std::vector<Image> tiles;
    Image currentTile;
    int offset = 10;
    Vec2<int> startPixels;
    Vec2<int> currentPosition;
    bool inMap = false;

    /// Functions ///
    void addTile(Vec2<int> position);
    void render();
};

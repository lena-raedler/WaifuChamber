//
// Created by bnorb on 16.02.20.
//

#pragma once

#include <string>
#include "../utils/utility.h"
#include "../utils/Image.h"
#include "../../game/GlobalObjects.h"


class Item2 {
public:
    /// Constructors ///
    Item2();
    Item2(std::string name, std::string imagePath, int value);
    ~Item2() = default;

    /// Fields ///
    Image itemImage;
    std::string name;
    int value;
};

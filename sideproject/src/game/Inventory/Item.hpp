//
// Created by bnorb on 27.01.20.
//

#pragma once

#include <string>
#include "../utils/Image.hpp"
#include "../utils/utility.h"

class Item {
public:
    Item();
    Item(std::string name, std::string imagePath, int value);
    ~Item();
    std::string getImagePath();

private:
    std::string name;
    std::string imagePath;
    int value;
};

//
// Created by bnorb on 27.01.20.
//

#pragma once

#include <string>
#include "../utils/Image.h"
#include "../utils/utility.h"

class Item {
public:
    Item();
    Item(std::string name, std::string imagePath, int value);
    ~Item();
    std::string getImagePath();
    std::string imagePath;

private:
    std::string name;
    int value;
};

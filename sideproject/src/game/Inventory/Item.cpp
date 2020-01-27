//
// Created by bnorb on 27.01.20.
//

#include "Item.hpp"
#include <utility>

Item::Item()
        : value(0)
{}

Item::Item(std::string name, std::string imagePath, int value)
        : name(name)
        , imagePath(imagePath)
        , value(value)
{
}

Item::~Item() = default;

std::string Item::getImagePath() {
    return imagePath;
}
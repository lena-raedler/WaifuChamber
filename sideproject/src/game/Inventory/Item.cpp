//
// Created by bnorb on 27.01.20.
//

#include "Item.hpp"
#include <utility>

Item::Item()
        : value(0)
{}

Item::Item(std::string name, std::string imagePath, int value)
        : imagePath(std::move(imagePath))
        , name(std::move(name))
        , value(value)
{}

Item::~Item() = default;

std::string Item::getImagePath() {
    return imagePath;
}
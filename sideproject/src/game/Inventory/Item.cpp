//
// Created by bnorb on 26.01.20.
//

#include "Item.hpp"
#include <utility>

Item::Item()
    : value(0)
{}

Item::Item(std::string& name, std::string& imagePath, int value)
    : name(std::move(name))
    , imagePath(std::move(imagePath))
    , value(value)
{}

Item::~Item() = default;
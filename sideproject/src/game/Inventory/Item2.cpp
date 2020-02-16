//
// Created by bnorb on 16.02.20.
//

#include "Item2.hpp"

Item2::Item2()
        : value(0)
{}

Item2::Item2(std::string name, std::string imagePath, int value)
        : itemImage(utility::loadImage(imagePath))
        , name(std::move(name))
        , value(value)
{}
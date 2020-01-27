//
// Created by bnorb on 26.01.20.
//

#include "ItemOld.hpp"
#include <utility>

ItemOld::ItemOld()
    : value(0)
{}

ItemOld::ItemOld(std::string& name, std::string& imagePath, int value)
    : name(std::move(name))
    , imagePath(std::move(imagePath))
    , value(value)
{}

ItemOld::~ItemOld() = default;
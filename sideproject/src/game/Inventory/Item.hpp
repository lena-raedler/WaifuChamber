//
// Created by bnorb on 26.01.20.
//

#pragma once

#include <string>

class Item {
public:
    Item();
    Item(std::string& name, std::string& imagePath, int value);
    ~Item();

private:
    std::string name;
    std::string imagePath;
    int value;
};


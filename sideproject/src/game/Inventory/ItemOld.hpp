//
// Created by bnorb on 26.01.20.
//

#pragma once

#include <string>

class ItemOld {
public:
    ItemOld();
    ItemOld(std::string& name, std::string& imagePath, int value);
    ~ItemOld();

private:
    std::string name;
    std::string imagePath;
    int value;
};


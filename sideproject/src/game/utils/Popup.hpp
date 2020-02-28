//
// Created by bnorb on 28.02.20.
//

#pragma once

#include <string>
#include "Text.hpp"

class Popup {
public:
    /// Constructors & Destructor ///
    Popup();
    Popup(std::string message);
    Popup(std::string message, int time);
    ~Popup() = default;

    /// Fields ///
    Text text;
    int time;
    int maxTime = 120;

    /// Functions ///
    void changePopup(std::string message);
    void displayPopup();
};

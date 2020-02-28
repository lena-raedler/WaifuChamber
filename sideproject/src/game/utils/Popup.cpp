//
// Created by bnorb on 28.02.20.
//

#include "Popup.hpp"

Popup::Popup()
    : Popup("", 120)
{}

Popup::Popup(std::string message)
    : Popup(message, 120)
{}

Popup::Popup(std::string message, int time)
    : text(Text(message))
    , time(time)
{}

void Popup::changePopup(std::string message) {
    text.changeText(message);
    time = maxTime;
}

void Popup::displayPopup() {
    if (time-- > 0) {
        text.render();
    }
}
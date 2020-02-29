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
    changePopup(message, maxTime);
}

void Popup::changePopup(std::string message, int timeTmp) {
    text.changeText(message);
    time = timeTmp;
}

void Popup::displayPopup() {
    if (time-- > 0) {
        text.render();
    }
}
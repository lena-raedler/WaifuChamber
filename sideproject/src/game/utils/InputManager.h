//
// Created by auki on 29.11.19.
//

#ifndef WAIFU_INPUTMANAGER_H
#define WAIFU_INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <cstdint>
#include "KeyboardMapping.h"

class InputManager {
public:
    const uint8_t* keyboard;
    bool isPressed(KeyboardKey key);
    bool keyDown[KEYBOARD_SIZE];
    bool keyUp[KEYBOARD_SIZE];
    bool update(); //returns false if user quits
    void init();
    void flush();
};


#endif //WAIFU_INPUTMANAGER_H

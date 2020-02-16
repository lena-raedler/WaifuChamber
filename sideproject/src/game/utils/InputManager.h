//
// Created by auki on 29.11.19.
//

#ifndef WAIFU_INPUTMANAGER_H
#define WAIFU_INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <cstdint>
#include "KeyboardMapping.h"
#include "Vec2.h"

class InputManager {
public:
    const uint8_t* keyboard;
    int mouseX;
    int mouseY;
    uint32_t mouse;
    bool isPressed(KeyboardKey key);
    bool isMousePressed(MouseButton button);
    bool isMouseHeld(MouseButton button);
    bool keyDown[KEYBOARD_SIZE];
    bool keyUp[KEYBOARD_SIZE];
    bool mouseDown[MOUSE_MAX];
    bool mouseUp[MOUSE_MAX];
    bool mouseHeld[MOUSE_MAX];
    bool update(); //returns false if user quits
    void init();
    void flush();

    Vec2<double> mouseVec();
};


#endif //WAIFU_INPUTMANAGER_H

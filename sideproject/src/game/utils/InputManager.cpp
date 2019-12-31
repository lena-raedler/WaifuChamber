//
// Created by auki on 29.11.19.
//

#include "InputManager.h"
void InputManager::init(){
    keyboard = SDL_GetKeyboardState(nullptr);
}
bool InputManager::update()
{
    for (int i = 0; i < KEYBOARD_SIZE; i++)
    {
        keyDown[i] = false;
        keyUp[i]   = false;
    }

    // Get key events from the OS
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        int index;
        switch (event.type)
        {
            case SDL_QUIT:
                return false;

            case SDL_KEYDOWN:
                keyboard = SDL_GetKeyboardState(nullptr);
                index = event.key.keysym.scancode;
                keyDown[index] = true;
                break;

            case SDL_KEYUP:
                keyboard = SDL_GetKeyboardState(nullptr);
                index = event.key.keysym.scancode;
                keyUp[index] = true;
                break;

            default:
                break;
        }
    }
    return true;
}

bool InputManager::isPressed(KeyboardKey key)
{

    if (!(keyboard))
        return false;

    int sdl_key = static_cast<int>(key);

    return keyboard[sdl_key] != 0;

}
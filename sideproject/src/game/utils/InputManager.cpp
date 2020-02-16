//
// Created by auki on 29.11.19.
//

#include "InputManager.h"
#include "Vec2.h"

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
    for (int i = 0; i < MOUSE_MAX; i++)
    {
        this->mouseDown[i] = false;
        this->mouseUp[i]   = false;
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

            case SDL_MOUSEMOTION:
                this->mouseX = event.motion.x; //cameraX
                this->mouseY = event.motion.y; //cameraY
                break;

            case SDL_MOUSEBUTTONDOWN:
                this->mouse = SDL_GetMouseState(&(this->mouseX),
                                                &(this->mouseY));

                if (event.button.button == SDL_BUTTON_LEFT) {
                    this->mouseDown[MOUSE_LEFT] = true;
                    this->mouseHeld[MOUSE_LEFT] = true;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    this->mouseDown[MOUSE_RIGHT] = true;
                    this->mouseHeld[MOUSE_RIGHT] = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                this->mouse = SDL_GetMouseState(&(this->mouseX),
                                                &(this->mouseY));

                if (event.button.button == SDL_BUTTON_LEFT) {
                    this->mouseHeld[MOUSE_LEFT] = false;
                    this->mouseUp[MOUSE_LEFT] = true;
                }

                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    this->mouseHeld[MOUSE_RIGHT] = false;
                    this->mouseUp[MOUSE_RIGHT] = true;
                }
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

bool InputManager::isMousePressed(MouseButton button)
{
    if (!(mouseDown))     // Always true
        return false;

    int sdl_key = static_cast<int>(button);
    return mouseDown[sdl_key] != 0;
}
bool InputManager::isMouseHeld(MouseButton button)
{
    if (!(mouseDown))     // Always true
        return false;

    int sdl_key = static_cast<int>(button);
    return mouseHeld[sdl_key] != 0;
}

void InputManager::flush() {
    for (int i = 0; i < KEYBOARD_SIZE; i++) {
        keyDown[i] = false;
        keyUp[i] = false;
    }
    for (int i = 0; i < MOUSE_MAX; i++) {
        this->mouseDown[i] = false;
        this->mouseUp[i]   = false;
    }
}

vec_t InputManager::mouseVec(){
    return{static_cast<double>(mouseX),static_cast<double>(mouseY)};
}
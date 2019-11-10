//
// Created by lena on 11/10/19.
//

#ifndef WAIFUCHAMBER_RENDERER_H
#define WAIFUCHAMBER_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


class Renderer {
public:
    Renderer();
    ~Renderer();
    // render present window
    void render();
    // clear renderer
    void clear();
    SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
    void renderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    // render texture onto a rectangle
    void renderTexture(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};


#endif //WAIFUCHAMBER_RENDERER_H

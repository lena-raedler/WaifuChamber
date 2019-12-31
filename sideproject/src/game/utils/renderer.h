//
// Created by lena on 11/10/19.
// wrapper class for SDL_Renderer
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
    void renderBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
    static SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    SDL_Renderer* getRenderer();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};


#endif //WAIFUCHAMBER_RENDERER_H

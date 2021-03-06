//
// Created by lena on 11/10/19.
// wrapper class for SDL_Renderer
//

#ifndef WAIFUCHAMBER_RENDERER_H
#define WAIFUCHAMBER_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include <vector>
#include <utility>
#include "triangle.h"
#include "../GlobalConstants.h"


class Renderer {
public:
    Renderer(std::pair<int, int> resolution);
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
    void renderTriangles(std::vector<triangle>& tris, int r, int g, int b, vec_t offset);
    static SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    SDL_Renderer* getRenderer();
    SDL_Surface* createSurface(std::string path);
    void renderSprite(SDL_Texture* texture, vec_t pos, SDL_Rect* rect);
    void renderSprite(SDL_Texture* texture, vec_t pos, SDL_Rect* rect, Vec2<int> size);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};


#endif //WAIFUCHAMBER_RENDERER_H

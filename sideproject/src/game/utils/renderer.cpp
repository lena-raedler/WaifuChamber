//
// Created by lena on 11/10/19.
// wrapper class for SDL_Renderer
//

#include "renderer.h"
#include <iostream>

Renderer::Renderer(std::pair<int, int> resolution) {
    window = SDL_CreateWindow("Waifu Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.first, resolution.second, SDL_WINDOW_FULLSCREEN_DESKTOP);     // TODO Width and height should be variables, not static numbers (see game.h)
    if(!window) {
        std::cerr << "failed to create window" << std::endl;
        throw  std::runtime_error("Could not open window");
    }

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        std::cerr << "failed to create renderer" << std::endl;
        throw std::runtime_error("Could not create renderer");
    }
}

Renderer::~Renderer() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if(window) {
        SDL_DestroyWindow(window);
    }
}

void Renderer::render() {
    SDL_RenderPresent(renderer);
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface *surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}

void Renderer::renderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::renderTexture(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect) {
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

SDL_Renderer* Renderer::getRenderer() {
    return renderer;
}

void Renderer::renderBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) {
    Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
    SDL_Color old;
    SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
    SDL_Rect bgrect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(renderer, &bgrect);
    SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int)((float)w * Percent);
    int px = x + (w - pw);
    SDL_Rect fgrect = { px, y, pw, h };
    SDL_RenderFillRect(renderer, &fgrect);
    SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
}
void Renderer::renderTriangles(std::vector<triangle>& tris, int r, int g, int b, vec_t offset){
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    for(auto t : tris){
        SDL_RenderDrawLine(renderer, t.a.x + offset.x, t.a.y + offset.y, t.b.x + offset.x, t.b.y + offset.y);
        SDL_RenderDrawLine(renderer, t.b.x + offset.x, t.b.y + offset.y, t.c.x + offset.x, t.c.y + offset.y);
        SDL_RenderDrawLine(renderer, t.a.x + offset.x, t.a.y + offset.y, t.c.x + offset.x, t.c.y + + offset.y);
    }

}

SDL_Color Renderer::color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color col = {r,g,b,a};
    return col;
}

SDL_Surface* Renderer::createSurface(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(!surface) {
        std::cerr << SDL_GetError() << std::endl;
        throw std::runtime_error("could not create surface");
    }
    return surface;
}

void Renderer::renderSprite(SDL_Texture *texture, vec_t pos, SDL_Rect *rect) {
    int x = (int) pos.x;
    int y = (int) pos.y;
    SDL_Rect renderRect = {x, y, GlobalConstants::tileSize, GlobalConstants::tileSize};
    //render to screen
    SDL_RenderCopy(renderer, texture, rect, &renderRect);
}

void Renderer::renderSprite(SDL_Texture *texture, vec_t pos, SDL_Rect *rect, Vec2<int> size) {
    int x = (int) pos.x;
    int y = (int) pos.y;
    SDL_Rect renderRect = {x, y, GlobalConstants::tileSize, GlobalConstants::tileSize};
    renderRect.w = rect->w * 2*size.x;
    renderRect.h = rect->h * 2*size.y;
    //render to screen
    SDL_RenderCopy(renderer, texture, rect, &renderRect);
}
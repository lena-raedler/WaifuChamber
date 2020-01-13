//
// Created by lena on 1/1/20.
//

#include "room.h"

Room::Room() {}

Room::Room(SDL_Texture *texture, SDL_Rect rectangle, std::unordered_map<SDL_Texture*, SDL_Rect> tileRectMap) {
    backgroundtexture = texture;
    backgroundRectangle = rectangle;
    tileMap = tileRectMap;
}

//Room::~Room() {}


void Room::render(Renderer &renderer) {
    renderer.renderTexture(backgroundtexture, nullptr, &backgroundRectangle);

    for(auto it = tileMap.begin(); it != tileMap.end(); it++) {
        renderer.renderTexture(it->first, nullptr, &(it->second));
    }

}
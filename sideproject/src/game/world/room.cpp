//
// Created by lena on 1/1/20.
//

#include "room.h"

Room::Room() {}

Room::Room(SDL_Texture *texture, SDL_Rect rectangle, std::unordered_map<SDL_Texture*, SDL_Rect> tileRectMap,
        std::vector<std::pair<int, int>> platformPositions, std::vector<std::pair<int, int>> gatePositions)
        : doorPositions(gatePositions) {
    backgroundtexture = texture;
    backgroundRectangle = rectangle;
    tileMap = tileRectMap;
    platformPositions = platformPositions;
}

Room::~Room() {}


void Room::render(Renderer &renderer) {
    renderer.renderTexture(backgroundtexture, nullptr, &backgroundRectangle);

    //for(auto it = tileMap.begin(); it != tileMap.end(); it++) {
    for(auto & it : tileMap) {
        renderer.renderTexture(it.first, nullptr, &(it.second));
    }

}
void Room::fillPlatformVector(std::vector<Platform>& p){
    p.clear();
    for(auto pair : platformPositions){
        p.push_back(Platform(pair, 0));
    }
    for(auto pair : wallPostitions) {
        p.push_back(Platform(pair, 1));
    }
    for(auto pair : ceilingPositions) {
        p.push_back(Platform(pair, 2));
    }
    for(auto pair : floorPositions) {
        p.push_back(Platform(pair, 3));
    }
}

void Room::printP() {
    for(auto i : platformPositions) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Room::clear() {
    SDL_DestroyTexture(backgroundtexture);
    for(auto &i : tileMap) {
        SDL_DestroyTexture(i.first);
    }
}
//
// Created by bnorb on 27.02.20.
//

#include "Map.hpp"

Map::Map() {
    currentPosition.x = 0;
    currentPosition.y = 0;
    startPixels.x = GlobalObjects::resolution.first;
    startPixels.y = GlobalObjects::resolution.second;
}

void Map::addTile(Vec2<int> position) {
    Image tile = utility::loadImage("files/textures/weapons/Arrow.png");
    tile.getRect()->x = startPixels.x + position.x*(GlobalConstants::tileSize + offset);
    tile.getRect()->y = startPixels.y + position.y*(GlobalConstants::tileSize + offset);
    tile.getRect()->w = GlobalConstants::tileSize;
    tile.getRect()->h = GlobalConstants::tileSize;
    tiles.push_back(tile);
}

void Map::render() {
    for (Image tile : tiles) {
        tile.render();
    }
}
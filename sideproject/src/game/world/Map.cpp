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

void Map::init() {
    initBackground();
    initVisitedTiles();
}

void Map::initBackground() {
    background = utility::loadImage("files/textures/map/Map2Transparent.png");
    background.getRect()->w = GlobalObjects::resolution.first;
    background.getRect()->h = GlobalObjects::resolution.second;
}

void Map::initVisitedTiles() {

}

void Map::addTile(Vec2<int> position) {
    Image tile = utility::loadImage("files/textures/map/VisitedTile2.png");
    tile.getRect()->x = startPixels.x + position.x*(GlobalConstants::tileSize + offset);
    tile.getRect()->y = startPixels.y + position.y*(GlobalConstants::tileSize + offset);
    tile.getRect()->w = GlobalConstants::tileSize;
    tile.getRect()->h = GlobalConstants::tileSize;

    Image tileHighlighted = utility::loadImage("files/textures/map/CurrentTile2.png");
    tileHighlighted.getRect()->x = tile.getRect()->x;
    tileHighlighted.getRect()->y = tile.getRect()->y;
    tileHighlighted.getRect()->w = tile.getRect()->w;
    tileHighlighted.getRect()->h = tile.getRect()->h;
    tiles.emplace_back(tile, tileHighlighted, position);
}

void Map::render() {
    background.render();

    for (MapTile tile : tiles) {
        if (tile.position == currentPosition)
            tile.renderHighlighted();
        else
            tile.render();
    }
}
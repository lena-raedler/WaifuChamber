//
// Created by bnorb on 27.02.20.
//

#include "Map.hpp"

Map::Map() {
    currentPosition.x = 0;
    currentPosition.y = 0;
    //startPixels.x = GlobalObjects::resolution.first;
    startPixels.x = 1920/2;
    //startPixels.y = GlobalObjects::resolution.second;
    startPixels.y = 1080/2;
}

/*
void Map::initCurrentTile() {
    Image tile = utility::loadImage("files/textures/brick_05.png");
    tile.getRect()->x = startPixels.x + currentPosition.x*(GlobalConstants::tileSize + offset);
    tile.getRect()->y = startPixels.y + currentPosition.y*(GlobalConstants::tileSize + offset);
    tile.getRect()->w = GlobalConstants::tileSize;
    tile.getRect()->h = GlobalConstants::tileSize;
    currentTile = MapTile(tile, currentPosition);
}
*/

void Map::addTile(Vec2<int> position) {
    std::cout << "x: " << startPixels.x << std::endl;
    std::cout << "y: " << startPixels.y << std::endl;

    Image tile = utility::loadImage("files/textures/brick_05.png");
    tile.getRect()->x = startPixels.x + position.x*(GlobalConstants::tileSize + offset);
    tile.getRect()->y = startPixels.y + position.y*(GlobalConstants::tileSize + offset);
    tile.getRect()->w = GlobalConstants::tileSize;
    tile.getRect()->h = GlobalConstants::tileSize;

    Image tileHighlighted = utility::loadImage("files/textures/brick_03.png");
    tileHighlighted.getRect()->x = tile.getRect()->x;
    tileHighlighted.getRect()->y = tile.getRect()->y;
    tileHighlighted.getRect()->w = tile.getRect()->w;
    tileHighlighted.getRect()->h = tile.getRect()->h;
    //tiles.push_back(MapTile(tile, position));
    tiles.push_back(MapTile(tile, tileHighlighted, position));
}

/*
void Map::updateCurrentTile() {
    currentTile.position = currentPosition;
    currentTile.image.getRect()->x = startPixels.x + currentPosition.x*(GlobalConstants::tileSize + offset);
    currentTile.image.getRect()->y = startPixels.y + currentPosition.y*(GlobalConstants::tileSize + offset);
}
 */

void Map::render() {
    for (MapTile tile : tiles) {
        if (tile.position == currentPosition) {
            //currentTile.render();
            tile.renderHighlighted();
        }
        else
            tile.render();
    }
}
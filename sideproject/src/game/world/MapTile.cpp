//
// Created by bnorb on 27.02.20.
//

#include "MapTile.hpp"

MapTile::MapTile()
    : MapTile(utility::loadImage("files/textures/brick_05.png"), utility::loadImage("files/textures/brick_03.png"), Vec2<int>{0, 0})
{}

MapTile::MapTile(Image image, Vec2<int> position)
    : MapTile(image, image, position)
{}

MapTile::MapTile(Image image, Image imageHighlighted, Vec2<int> position)
    : image(image)
    , imageHighlighted(imageHighlighted)
    , position(position)
{}

void MapTile::render() {
    image.render();
}

void MapTile::renderHighlighted() {
    imageHighlighted.render();
}
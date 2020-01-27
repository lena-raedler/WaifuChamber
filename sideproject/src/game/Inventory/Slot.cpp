//
// Created by bnorb on 27.01.20.
//

#include "Slot.hpp"

Slot::Slot() = default;

Slot::Slot(Renderer& renderer, Vec2<int> position)
    : available(false)
    , background{position.x, position.y, GlobalConstants::tileSize, GlobalConstants::tileSize}
    , position(position)
    , renderer(&renderer)
{}

Slot::Slot(Item item, Renderer& renderer, Vec2<int> position)
        : item(item)
        , itemImage(utility::loadImage(item.getImagePath(), renderer))
        , available(true)
        , background{position.x, position.y, GlobalConstants::tileSize, GlobalConstants::tileSize}
        , position(position)
        , renderer(&renderer)
{
    itemImage.getRect()->w = GlobalConstants::tileSize;
    itemImage.getRect()->h = GlobalConstants::tileSize;
    itemImage.getRect()->x = position.x;
    itemImage.getRect()->y = position.y;
}

Slot::~Slot() = default;

void Slot::renderSlot() {
    // Gray background
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderFillRect(renderer->getRenderer(), &background);

    if(available)
        itemImage.render(*renderer);
}

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
        : itemImage(utility::loadImage(item.getImagePath(), renderer))
        , item(item)
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

void Slot::changeItem(Item& newItem) {
    item = newItem;
    available = true;
}

void Slot::removeItem() {
    item = Item();
    available = false;
}

void Slot::loadNewItemImage(std::string path) {
    itemImage = utility::loadImage(path, *renderer);
    itemImage.getRect()->w = GlobalConstants::tileSize;
    itemImage.getRect()->h = GlobalConstants::tileSize;
    itemImage.getRect()->x = position.x;
    itemImage.getRect()->y = position.y;
}

void Slot::renderSlot() {
    // Gray background
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderFillRect(renderer->getRenderer(), &background);

    if(available)
        itemImage.render(*renderer);
}
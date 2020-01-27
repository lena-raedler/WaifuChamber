//
// Created by bnorb on 26.01.20.
//

#include "SlotOld.hpp"

SlotOld::SlotOld() = default;

SlotOld::SlotOld(const std::string& path, Renderer& renderer, Vec2<int> position)
    : available(false)
    , path(path)
    , background{position.x, position.y, GlobalConstants::tileSize, GlobalConstants::tileSize}
    , position(position)
    , renderer(&renderer)
{
    image = utility::loadImage(path, renderer);
    image.getRect()->w = GlobalConstants::tileSize;
    image.getRect()->h = GlobalConstants::tileSize;
    image.getRect()->x = position.x;
    image.getRect()->y = position.y;
}

SlotOld::~SlotOld() = default;

void SlotOld::renderSlot() {
    // Gray background
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderFillRect(renderer->getRenderer(), &background);

    if (available)
        image.render(*renderer);
}

void SlotOld::changePath(const std::string& newPath) {
    path = newPath;
}

void SlotOld::setAvailable(bool availableNew) {
    available = availableNew;
}
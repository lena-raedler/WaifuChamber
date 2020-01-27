//
// Created by bnorb on 27.01.20.
//

#pragma once

#include "SDL2/SDL.h"
#include "../utils/Image.hpp"
#include "../utils/utility.h"
#include "../GlobalConstants.h"
#include "Item.hpp"
#include <memory>

class Slot {
public:
    Slot();
    Slot(Renderer&, Vec2<int> position);
    Slot(Item item, Renderer& renderer, Vec2<int> position);
    ~Slot();
    void renderSlot();
    void changeItem(Item& item);
    void removeItem();
    Image itemImage;
    void loadNewItemImage(std::string path);

private:
    Item item;
    bool available;
    SDL_Rect background;
    Vec2<int> position;
    Renderer* renderer;
};
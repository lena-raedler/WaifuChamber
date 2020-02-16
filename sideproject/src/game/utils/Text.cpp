//
// Created by bnorb on 16.02.20.
//

#include "Text.hpp"

#include <utility>

Text::Text()
    : Text("Hello, I am a sample text :)", "files/freefont-20120503/FreeSerif.ttf", 40, {0xFF, 0xFF, 0xFF}, 0, 0)
{}

Text::Text(std::string message)
    : Text(message, "files/freefont-20120503/FreeSerif.ttf", 40, {0xFF, 0xFF, 0xFF}, 0, 0)
{}

Text::Text(std::string message, int fontSize, SDL_Color messageColor)
    : Text(message, "files/freefont-20120503/FreeSerif.ttf", fontSize, messageColor, 0, 0)
{}

Text::Text(std::string message, std::string fontPath, int fontSize, SDL_Color messageColor)
    : Text(message, fontPath, fontSize, messageColor, 0, 0)
{}

// If I pass message and fontPath as a reference the other constructors throw errors
Text::Text(std::string message, std::string fontPath, int fontSize, SDL_Color messageColor, int x, int y)
    : font(utility::loadFont(fontPath, fontSize))
    , message(message)
    , fontSize(fontSize)
    , messageColor(messageColor)
{
    if (font == nullptr) {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else {
        loadText();


        //Render text
        //fontTexture = utility::loadFromRenderedText(font, text, messageColor, positionSize);
        //if (fontTexture == nullptr) {
        //    printf( "Failed to render text texture!\n" );
        //}
        //else {
            //positionSize.x = x;
            //positionSize.y = y;

            rect.x = x;
            rect.y = y;
        //}
    }
}


void Text::changeText(std::string newMessage) {
    message = newMessage;
    loadText();
}
void Text::changeFontSize(int newFontSize) {
    fontSize = newFontSize;
    loadText();
}
void Text::changeColor(SDL_Color newMessageColor) {
    messageColor = newMessageColor;
    loadText();
}
void Text::changeText(std::string newMessage, int newFontSize, SDL_Color newMessageColor) {
    message = newMessage;
    fontSize = newFontSize;
    messageColor = newMessageColor;
    loadText();
}

void Text::loadText() {
    //Render text
    fontTexture = utility::loadFromRenderedText(font, message, messageColor, rect);
    if (fontTexture == nullptr) {
        printf( "Failed to render text texture!\n");
    }
}

void Text::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    //Set rendering space and render to screen
    //SDL_Rect rect = {positionSize.x, positionSize.y, positionSize.width, positionSize.height};
    //rect = {positionSize.x, positionSize.y, positionSize.width, positionSize.height};

    //Set clip rendering dimensions
    if (clip != nullptr) {
        rect.w = clip->w;
        rect.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( GlobalObjects::renderPtr->getRenderer(), fontTexture, clip, &rect, angle, center, flip );
}
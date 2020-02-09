//
// Created by bnorb on 09.02.20.
//

#include "OptionsMenu.hpp"

OptionsMenu::OptionsMenu(Renderer& renderer) {
    int width = 299;    // Exact size of the button textures
    int height = 84;
    int widthGap = 25;
    int heightGap = 25;
    int x = 1920 / 2 - width / 2 - width - widthGap;
    int y = 1080 / 2 - height / 2 - height*2 - heightGap*2;

    decreaseVolumeButton = Button(renderer, "files/textures/menu/options/decrease_volume.png", "files/textures/menu/options/decrease_volume_highlighted.png", x, y, width, height);

    volumeImage = utility::loadImage("files/textures/menu/options/increase_volume.png", renderer);  // TODO Change file path
    volumeImage.getRect()->x = decreaseVolumeButton.x + decreaseVolumeButton.width + widthGap;
    volumeImage.getRect()->y = decreaseVolumeButton.y;
    volumeImage.getRect()->w = decreaseVolumeButton.width;
    volumeImage.getRect()->h = decreaseVolumeButton.height;

    increaseVolumeButton = Button(renderer, "files/textures/menu/options/increase_volume.png", "files/textures/menu/options/increase_volume_highlighted.png", x + width * 2 + widthGap * 2, y, width, height);

    increaseVolume = false;
    decreaseVolume = false;
}

void OptionsMenu::renderOptionsMenu(Renderer& renderer) {
    increaseVolumeButton.renderButton(renderer);
    volumeImage.render(renderer);
    decreaseVolumeButton.renderButton(renderer);

    increaseVolumeButton.highlighted = false;
    decreaseVolumeButton.highlighted = false;
    //increaseVolume = false;
    //decreaseVolume = false;
}

void  OptionsMenu::resolveMouseInput(int mouseX, int mouseY, bool clicked) {
    if (increaseVolumeButton.inButton(mouseX, mouseY)) {
        increaseVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            increaseVolume = true;
        }
    }
    else if (decreaseVolumeButton.inButton(mouseX, mouseY)) {
        decreaseVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            decreaseVolume = true;
        }
    }
}
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

    volumeImages = std::vector<Image>(10);

    volume = 5;     // Default, goes from 1 to 10
    for (int i = 0; i < 10; i++) {
        volumeImages[i] = utility::loadImage("files/textures/menu/options/volume_" + std::to_string(i+1) + ".png", renderer);
        volumeImages[i].getRect()->x = decreaseVolumeButton.x + decreaseVolumeButton.width + widthGap;
        volumeImages[i].getRect()->y = decreaseVolumeButton.y;
        volumeImages[i].getRect()->w = decreaseVolumeButton.width;
        volumeImages[i].getRect()->h = decreaseVolumeButton.height;
    }
    /*
    volumeImage = utility::loadImage("files/textures/menu/options/volume_" + std::to_string(volume) + ".png", renderer);  // TODO Change file path
    volumeImage.getRect()->x = decreaseVolumeButton.x + decreaseVolumeButton.width + widthGap;
    volumeImage.getRect()->y = decreaseVolumeButton.y;
    volumeImage.getRect()->w = decreaseVolumeButton.width;
    volumeImage.getRect()->h = decreaseVolumeButton.height;
    */

    increaseVolumeButton = Button(renderer, "files/textures/menu/options/increase_volume.png", "files/textures/menu/options/increase_volume_highlighted.png", x + width * 2 + widthGap * 2, y, width, height);

    increaseVolume = false;
    decreaseVolume = false;
}

void OptionsMenu::renderOptionsMenu(Renderer& renderer) {
    increaseVolumeButton.renderButton(renderer);
    //volumeImage.render(renderer);
    volumeImages[volume-1].render(renderer);
    decreaseVolumeButton.renderButton(renderer);

    increaseVolumeButton.highlighted = false;
    decreaseVolumeButton.highlighted = false;
    //increaseVolume = false;
    //decreaseVolume = false;
}

void OptionsMenu::resolveMouseInput(int mouseX, int mouseY, bool clicked) {
    if (increaseVolumeButton.inButton(mouseX, mouseY)) {
        increaseVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            increaseVolume = true;
            if (volume < 10)
                volume++;
        }
    }
    else if (decreaseVolumeButton.inButton(mouseX, mouseY)) {
        decreaseVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            decreaseVolume = true;
            if (volume > 1)
                volume--;
        }
    }
}
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
    decreaseEffectVolumeButton = Button(renderer, "files/textures/menu/options/decrease_volume.png", "files/textures/menu/options/decrease_volume_highlighted.png", x, y+height+heightGap, width, height);

    volumeImages = std::vector<Image>(11);
    effectVolumeImages = std::vector<Image>(11);

    volume = 5;     // Default, goes from 1 to 10
    effectVolume = 5;

    for (int i = 0; i < 11; i++) {
        volumeImages[i] = utility::loadImage("files/textures/menu/options/volume_" + std::to_string(i) + ".png", renderer);
        volumeImages[i].getRect()->x = decreaseVolumeButton.x + decreaseVolumeButton.width + widthGap;
        volumeImages[i].getRect()->y = decreaseVolumeButton.y;
        volumeImages[i].getRect()->w = decreaseVolumeButton.width;
        volumeImages[i].getRect()->h = decreaseVolumeButton.height;

        effectVolumeImages[i] = volumeImages[i];
        effectVolumeImages[i].getRect()->y += height + heightGap;
    }

    increaseVolumeButton = Button(renderer, "files/textures/menu/options/increase_volume.png", "files/textures/menu/options/increase_volume_highlighted.png", x + width * 2 + widthGap * 2, y, width, height);
    increaseEffectVolumeButton = Button(renderer, "files/textures/menu/options/increase_volume.png", "files/textures/menu/options/increase_volume_highlighted.png", x + width * 2 + widthGap * 2, y+height+heightGap, width, height);

    increaseVolume = false;
    decreaseVolume = false;
    increaseEffectVolume = false;
    decreaseEffectVolume = false;
}

void OptionsMenu::renderOptionsMenu(Renderer& renderer) {
    increaseVolumeButton.renderButton(renderer);
    volumeImages[volume].render(renderer);
    decreaseVolumeButton.renderButton(renderer);

    increaseEffectVolumeButton.renderButton(renderer);
    effectVolumeImages[effectVolume].render(renderer);
    decreaseEffectVolumeButton.renderButton(renderer);

    increaseVolumeButton.highlighted = false;
    decreaseVolumeButton.highlighted = false;

    increaseEffectVolumeButton.highlighted = false;
    decreaseEffectVolumeButton.highlighted = false;

    //increaseVolume = false;
    //decreaseVolume = false;
    // I AM THE BUTTON MASTER!
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
            if (volume > 0)
                volume--;
        }
    }
    else if (increaseEffectVolumeButton.inButton(mouseX, mouseY)) {
        increaseEffectVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            increaseEffectVolume = true;
            if (effectVolume < 10)
                effectVolume++;
        }
    }
    else if (decreaseEffectVolumeButton.inButton(mouseX, mouseY)) {
        decreaseEffectVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            decreaseEffectVolume = true;
            if (effectVolume > 0)
                effectVolume--;
        }
    }
}
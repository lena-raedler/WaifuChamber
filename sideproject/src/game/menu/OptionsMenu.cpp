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

    decreaseEffectVolumeButton = Button(renderer, "files/textures/menu/options/decrease_effect_volume.png", "files/textures/menu/options/decrease_effect_volume_highlighted.png", x, y, width, height);
    decreaseMusicVolumeButton = Button(renderer, "files/textures/menu/options/decrease_music_volume.png", "files/textures/menu/options/decrease_music_volume_highlighted.png", x, y+height+heightGap, width, height);

    musicVolumeImages = std::vector<Image>(11);
    effectVolumeImages = std::vector<Image>(11);

    effectVolume = 5;   // Default, goes from 1 to 10
    musicVolume = 5;

    for (int i = 0; i < 11; i++) {
        effectVolumeImages[i] = utility::loadImage("files/textures/menu/options/volume_" + std::to_string(i) + ".png", renderer);
        effectVolumeImages[i].getRect()->x = decreaseEffectVolumeButton.x + decreaseEffectVolumeButton.width + widthGap;
        effectVolumeImages[i].getRect()->y = decreaseEffectVolumeButton.y;
        effectVolumeImages[i].getRect()->w = decreaseEffectVolumeButton.width;
        effectVolumeImages[i].getRect()->h = decreaseEffectVolumeButton.height;

        musicVolumeImages[i] = effectVolumeImages[i];
        musicVolumeImages[i].getRect()->y += height + heightGap;
    }

    increaseEffectVolumeButton = Button(renderer, "files/textures/menu/options/increase_effect_volume.png", "files/textures/menu/options/increase_effect_volume_highlighted.png", x + width * 2 + widthGap * 2, y, width, height);
    increaseMusicVolumeButton = Button(renderer, "files/textures/menu/options/increase_music_volume.png", "files/textures/menu/options/increase_music_volume_highlighted.png", x + width * 2 + widthGap * 2, y+height+heightGap, width, height);

    increaseEffectVolume = false;
    decreaseEffectVolume = false;
    increaseMusicVolume = false;
    decreaseMusicVolume = false;
}

void OptionsMenu::renderOptionsMenu(Renderer& renderer) {
    increaseEffectVolumeButton.renderButton(renderer);
    effectVolumeImages[effectVolume].render(renderer);
    decreaseEffectVolumeButton.renderButton(renderer);

    increaseMusicVolumeButton.renderButton(renderer);
    musicVolumeImages[musicVolume].render(renderer);
    decreaseMusicVolumeButton.renderButton(renderer);

    increaseEffectVolumeButton.highlighted = false;
    decreaseEffectVolumeButton.highlighted = false;

    increaseMusicVolumeButton.highlighted = false;
    decreaseMusicVolumeButton.highlighted = false;
}

void OptionsMenu::resolveMouseInput(int mouseX, int mouseY, bool clicked) {
    if (increaseEffectVolumeButton.inButton(mouseX, mouseY)) {
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
    else if (increaseMusicVolumeButton.inButton(mouseX, mouseY)) {
        increaseMusicVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            increaseMusicVolume = true;
            if (musicVolume < 10)
                musicVolume++;
        }
    }
    else if (decreaseMusicVolumeButton.inButton(mouseX, mouseY)) {
        decreaseMusicVolumeButton.highlighted = true;
        if (clicked) {      // Unpause or start the game
            decreaseMusicVolume = true;
            if (musicVolume > 0)
                musicVolume--;
        }
    }
}
# Waifu Quest
Final version of our project for the [Advanced C++](https://git.uibk.ac.at/c7031162/703807-advanced-cxx "Advanced C++") course winter semester 2019 at the University of Innsbruck.

## Authors
- [Lukas Aukenthaler](https://github.com/DrGurk "Lukas") <lukas.aukenthaler@student.uibk.ac.at>
- [Bernd Menia](https://github.com/BerndMenia "Bernd Menia") <bernd.menia@student.uibk.ac.at>
- [Lena Rädler](https://github.com/lena-raedler "Lena Rädler") <.raedler@student.uibk.ac.at>

## Prerequisites
- C++ version >= 17
- [CMake](https://cmake.org/ "CMake") version >= 3.10
- [SDL2](https://www.libsdl.org/ "SDL") version >= 2.0.0
- [SDL2_Image](https://www.libsdl.org/projects/SDL_image/ "SDL_image") version >= 2.0.0
- [SDL2_TTF](https://www.libsdl.org/projects/SDL_ttf/ "SDL_ttf") version >= 2.0.0
- [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/ "SDL_mixer") version >= 2.0
- [SDL2_gfx](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/ "SDL2_gfx") version >= 1.0.4
- [Boost](https://www.boost.org/ "Boost C++")

## Installion and Start
All tools that are listed in the Prerequisites chapter must be installed beforehand or the program will crash. After everything is installed either build and start the program through an IDE (e.g. CLion, Visual Studio) or execute the following lines within the /game directory: 

```bash
foo@bar:~$ cmake CMakeLists.txt 
foo@bar:~$ make
foo@bar:~$ ./waifu
``` 

## Custom Specifications
Initially we were tasked to program a top down RPG like Pokémon, but we decided to take on the task from the previous year, which was to create a Metroidvania-like sidescroller. From the custom_spec.txt file that we provided at the start of this project we have completed the following objecives (optional specs in bold): 

- 3 consecutive areas, each:
    - [x] with its own tone (architecture, sprites, music, enemies etc)
    - [x] with a handful of rooms each
    - [x] a boss guarding an item / ability
    - [x] more difficult than the previous area
    - [x] containing save points
    - [x] containing unlockable shortcuts leading back to the checkpoint (á la Hollow Knight/Salt and Sanctuary)
    + [ ] **final area = first area with changes**
- basic movement
    - [x] running left / right
    - [x] jumping
    - [ ] dropping from platforms
    - [x] interacting with game entities (save points, doors etc)
    + [ ] **dodge roll (with air dash being unlockable)**
    - [x] some form of consecutive jump (jump resets or double jump)
- main combat
    - [x] melee and/or ranged
    - [x] hitting enemies
    - [x] getting hit by enemies
    + [ ] **swappable special move**
    + [ ] **dodge / parry projectiles**
- player character
    - [x] gets stronger over the course of the game (XP / level-up)
    - [ ] can equip found items to further increase stats
- non-hostile NPCs
    - [ ] shopkeeper that take your hard earned currency
    + [ ] **small questlines**
    - [ ] a sort of safe hub with multiple NPCs
- enemies
    - [x] attack the player character as it gets in range
    - [x] variants with melee attacks
    - [x] variants with ranged attacks
    - [x] bosses are capable of using different attacks
    + [x] **late game bosses have multiple phases**
- map
    - [x] shows discovered rooms and their doorways
    - [ ] shows discovered save points
    - [x] shows where the player is currently located
- game over
    - [x] player dies
    - [ ] player defeats final boss
+ new game+
    + [ ] **ability to restart the game after completion, keeping your equipment (sans key items) and scaling enemies accordingly**
- main menu
    - options
        + [ ] **fully rebindable keys**
        + [ ] **controller support**
    - [x] new game
    - [x] load game
    - [x] exit
- pause menu
    - [x] access to options menu
    - [ ] shows player stats
    - [ ] inventory management
    - [x] continue
    - [ ] go to main menu
- *internals*
    - [x] cap the frame-rate at a reasonable number
    - [x] timing related logic should be independent of the frame-rate, use a *time delta* 

\
While working on the project we included a lot of other features that we found fitting. Some of them are: 

- [x] Locked doors that can be unlocked with a key
- [x] Text popup when receiving a key or an item (e.g. float, double jump)
- [x] Player and enemy sprites to mimic movement in both directions and a default animation while standing still
- [x] Status effects (bleeding, shocked), they are visible when applied
- [x] Sound effects (shooting, jumping, dying, pressing a button, ...)
- [x] Music- and effect volume can be controlled within the options menu
- [x] 

There are more, but they are either too miniscule to list or there are too many to list them all. 

## Work in Progress
The textures for the player projectiles are displaced a little bit in comparison to their hitbox. We therefore recommend playing with the debug option turned on (turn on and off within the option menu in-game) so that the hitbox is visible. 
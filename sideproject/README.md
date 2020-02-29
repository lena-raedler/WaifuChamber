# Waifu Quest
Final version of our project for the [Advanced C++](https://git.uibk.ac.at/c7031162/703807-advanced-cxx "Advanced C++") course winter semester 2019 at the University of Innsbruck.

## Authors
- [Lukas Aukenthaler](https://github.com/DrGurk "Lukas") <lukas.aukenthaler@student.uibk.ac.at>
- [Bernd Menia](https://github.com/BerndMenia "Bernd Menia") <bernd.menia@student.uibk.ac.at>
- [Lena Rädler](https://github.com/lena-raedler "Lena Rädler") <anna-lena.raedler@student.uibk.ac.at>

## Prerequisites
- C++ version >= 17
- [CMake](https://cmake.org/ "CMake") version >= 3.10
- [SDL2](https://www.libsdl.org/ "SDL") version >= 2.0.0
- [SDL2_Image](https://www.libsdl.org/projects/SDL_image/ "SDL_image") version >= 2.0.0
- [SDL2_TTF](https://www.libsdl.org/projects/SDL_ttf/ "SDL_ttf") version >= 2.0.0
- [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/ "SDL_mixer") version >= 2.0
- [SDL2_gfx](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/ "SDL2_gfx") version >= 1.0.4
- [Boost](https://www.boost.org/ "Boost C++")

## Installation and Start
All tools that are listed in the Prerequisites chapter must be installed beforehand or the program will crash. After everything is installed either build and start the program through an IDE (e.g. CLion, Visual Studio) or execute the following lines within the /src directory: 

```bash
foo@bar:~$ cmake CMakeLists.txt 
foo@bar:~$ make
foo@bar:~$ ./waifu
``` 

Within the options menu you can turn Debug on and off. We recommend playing with Debug on due to some bugs and exact hitbox textures. 

## How to Play
| Key                   | Effect                | Comment   |
|:---------------------:|:---------------------:|:---------:|
| W / Space             | Jump                  | Resets when grounded, double jump is collectable           |
| S                     | Float                 | Hold to float, drains stamina |
| A                     | Move left             |           |
| B                     | Move right            |           |
| E                     | Pickup items          | Pickup keys |
| R                     | Fully heal character  | Used to easily playtest the game. Doesn't drain uses |
| T                     | Fully heal character | Normal usage of healing potion drains usage |
| Y                     | Reset healing potion usages | Was initially used for playtesting, but can be used at will|
| M                     | Map                   | Does not get saved! Only shows visited rooms and the current room for this session |
| Shift + Left mouse button | Dash              | A helper circle shows where the player will dash to |
| Left mouse button     | Shoot projectile | The projectile moves towards the position of the mouse at the time of using |
| Escape | Display menu, pause game, go one step back | Overloaded key depending on the use case |
| O | Exit game | Exits immediately in case the program is stuck or something doesn't work as intended |

When the game is started the player is greeted with the main menu. From there options can be set (don't forget to save!), the game can be exit or started. When the game is started the player starts at the last checkpoint. 

To start the game anew the player has to do one of two things:
 
- Manually change the values in the /savegame.txt file (check game/SavedVariables.def to see which line corresponds to which entry)

- Replace /savegame.txt with /savegame_fresh.txt

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
    + [x] **dodge roll (with air dash being unlockable)**
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
- [x] Popup text when receiving a key or an item (e.g. float, double jump)
- [x] Player and enemy sprites to mimic movement in both directions and a default animation while standing still
- [x] Status effects (bleeding, shocked), they are visible when applied
- [x] Sound effects (shooting, jumping, dying, pressing a button, ...)
- [x] Music- and effect volume can be controlled within the options menu
- [x] Bosses have telgraphed attacks (attack that have a charge up time and then have a big area of effect)
- [x] Float ability (uses stamina)
- [x] Manual save through the menu
- [x] Healing potion that can be used three times (reset by pressing 'y') that fully heals the player (estus is bestus). When empty an empty healing potion gets displayed
- [x] Tutorial level that teaches the player how to play the game (when moving to the red boxes (hitboxes) a message gets displayed)
- [x] Wallclimb when being close to the top of a platform
- [x] Enemies have different types (standing still, move towards the player, patroling)
- [x] Bosses have names that are displayed over their health bars. 

There are more, but they are either too miniscule to list or there are too many to list them all. 

## Known Major Bugs
- The textures for the player projectiles are displaced a little bit in comparison to their hitbox. We therefore recommend playing with the debug option turned on (turn on and off within the option menu in-game) so that the hitbox is visible. 

- The game can get laggy from time to time (especially when starting, changing rooms or when a lot of projectiles and / or enemies are displayed)

- When the game lags it can happen that the player falls through floors (not out of bounds though)

- When the player is right next to a wall (next pixel), a platform is above them and they jump then the player hits the platform with their head and falls down again. 


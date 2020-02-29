# Waifu Quest
Final version of our project for the [Advanced C++](https://git.uibk.ac.at/c7031162/703807-advanced-cxx "Advanced C++") course winter semester 2019 at the University of Innsbruck.

## Authors
- [Lukas Aukenthaler](https://github.com/DrGurk "DrGurk") <lukas.aukenthaler@student.uibk.ac.at>
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
Initially we were tasked to program a top down RPG like Pokémon, but we decided to take on the task from the previous year, which was to create a Metroidvania-like sidescroller. From the custom_spec.txt file that we provided at the start of this project we have completed the following objectives: 

- 

## Work in Progress
The textures for the player projectiles are displaced a little bit in comparison to their hitbox. We therefore recommend playing with the debug option turned on (turn on and off within the option menu in-game) so that the hitbox is visible. 
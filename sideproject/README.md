# Waifu Quest
Final version of our project for the Advanced C++ course winter semester 2019 at the University of Innsbruck. 

## Prerequisites
- C++ 17 or higher
- CMake version 3.10 or higher 
- SDL2 version 2.0.0 or higher
- SDL2_Image version 2.0.0 or higher
- SDL2_TTF version 2.0.0 or higher
- SDL2_Mixer
- SDL2_GFX

## Installing
All tools that are listed in the Prerequisites chapter must be installed beforehand or the program will crash. After everything is installed either build and start the program through an IDE (e.g. CLion, Visual Studio) or execute the following lines within the /game directory: 

```bash
foo@bar:~$ cmake CMakeLists.txt 
foo@bar:~$ make
foo@bar:~$ ./waifu
``` 

## Custom Specifications
Initially we were tasked to program a top down RPG like Pokémon, but we decided to take on the task from the previous year, which was to create a Metroidvania-like sidescroller. From the custom_spec.txt file that we provided at the start of this project we have completed the following objectives: 

- 
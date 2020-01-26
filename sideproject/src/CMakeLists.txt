cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")

project(waifu)

add_subdirectory(game)
include(FindPkgConfig)
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
find_library(SDL_MIXER_LIBRARY
        NAMES SDL2_mixer
        HINTS
        ENV SDLMIXERDIR
        ENV SDLDIR
        PATH_SUFFIXES lib
        )

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(waifu main.cpp game/game.cpp game/entities/player/player.cpp game/utils/renderer.cpp game/entities/player/Movable.cpp game/utils/InputManager.cpp game/utils/InputManager.h game/utils/KeyboardMapping.h game/utils/utility.h game/utils/utility.cpp game/world/room.h game/world/room.cpp game/utils/image.h game/utils/image.cpp game/entities/player/Projectile.cpp game/utils/ImageNew.cpp game/utils/ImageNew.hpp game/world/Gate.cpp game/world/Gate.h game/world/Platform.cpp game/world/Platform.h game/GlobalConstants.h game/GlobalObjects.h game/GlobalConstants.cpp game/GlobalConstants.h)

target_link_libraries(waifu ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARY})

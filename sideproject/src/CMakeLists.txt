cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")

# QT Widget
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

project(waifu)

add_subdirectory(game)
include(FindPkgConfig)
find_package(SDL2 REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
find_library(SDL_MIXER_LIBRARY
        NAMES SDL2_mixer
        HINTS
        ENV SDLMIXERDIR
        ENV SDLDIR
        PATH_SUFFIXES lib
        )

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(waifu main.cpp game/game.cpp game/entities/player/player.cpp game/utils/renderer.cpp game/entities/player/Movable.cpp game/utils/InputManager.cpp game/utils/InputManager.h game/utils/KeyboardMapping.h game/utils/utility.h game/utils/utility.cpp game/world/room.h game/world/room.cpp game/entities/player/Projectile.cpp game/utils/Image.cpp game/utils/Image.hpp game/world/Gate.cpp game/world/Gate.h game/world/Platform.cpp game/world/Platform.h game/GlobalConstants.h game/GlobalObjects.h game/GlobalConstants.cpp game/GlobalConstants.h game/SavedVariables.cpp game/SavedVariables.h game/Inventory/Inventory.cpp game/Inventory/Inventory.hpp game/Inventory/Slot.cpp game/Inventory/Slot.hpp game/entities/player/Enemy.cpp game/entities/player/Enemy.h game/entities/player/Ability.cpp game/entities/player/Ability.h game/Inventory/Item.cpp game/Inventory/Item.hpp game/Inventory/Item.cpp game/Inventory/Item.hpp game/Inventory/RangedWeapon.cpp game/Inventory/RangedWeapon.hpp game/entities/player/EnemyBuilder.h game/Inventory/EstusFlask.cpp game/Inventory/EstusFlask.hpp game/entities/player/Boss.cpp game/entities/player/Boss.h game/entities/player/Bar.cpp game/entities/player/Bar.hpp game/entities/player/EnemyBuilder.cpp game/entities/player/EnemyBuilder.h game/utils/Rgba.hpp game/world/gateInformation.h game/menu/Menu.cpp game/menu/Menu.hpp game/menu/Button.cpp game/menu/Button.hpp)

target_link_libraries(waifu ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARY})


#target_link_libraries(waifu ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARY} Qt5::Widgets)
#target_link_libraries(waifu Qt5::Widgets)

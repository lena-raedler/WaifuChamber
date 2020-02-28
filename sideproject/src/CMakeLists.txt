cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")

# QT Widget
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

project(waifu)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmakemodules")
add_subdirectory(game)
include(FindPkgConfig)
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
find_library(SDL_MIXER_LIBRARY
        SDL2_GFX_LIBRARIES
        NAMES SDL2_mixer
        HINTS
        ENV SDLMIXERDIR
        ENV SDLDIR
        PATH_SUFFIXES lib
        )

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${SDL2_GFX_INCLUDE_LIBRARIES})

add_executable(waifu main.cpp game/game.cpp game/entities/player/player.cpp game/utils/renderer.cpp game/entities/player/Movable.cpp game/utils/InputManager.cpp game/utils/InputManager.h game/utils/KeyboardMapping.h game/utils/utility.h game/utils/utility.cpp game/world/room.h game/world/room.cpp game/entities/player/Projectile.cpp game/utils/Image.cpp game/utils/Image.h game/world/Gate.cpp game/world/Gate.h game/world/Platform.cpp game/world/Platform.h game/GlobalConstants.h game/GlobalObjects.h game/GlobalConstants.cpp game/GlobalConstants.h game/SavedVariables.cpp game/SavedVariables.h game/Inventory/Inventory.cpp game/Inventory/Inventory.hpp game/Inventory/Slot.cpp game/Inventory/Slot.hpp game/entities/player/Enemy.cpp game/entities/player/Enemy.h game/entities/player/Ability.cpp game/entities/player/Ability.h game/Inventory/Item.cpp game/Inventory/Item.hpp game/Inventory/Item.cpp game/Inventory/Item.hpp game/Inventory/RangedWeapon.cpp game/Inventory/RangedWeapon.hpp game/entities/player/EnemyBuilder.h game/Inventory/EstusFlask.cpp game/Inventory/EstusFlask.hpp game/entities/player/Boss.cpp game/entities/player/Boss.h game/entities/player/Bar.cpp game/entities/player/Bar.hpp game/entities/player/EnemyBuilder.cpp game/entities/player/EnemyBuilder.h game/utils/Rgba.h game/world/gateInformation.h game/menu/Menu.cpp game/menu/Menu.hpp game/menu/OptionsMenu.cpp game/menu/OptionsMenu.hpp game/menu/Button.cpp game/menu/Button.hpp game/entities/player/AbilityPicker.h game/world/LockedWall.h game/entities/player/SoundEffect.h game/entities/player/TelegraphedAbility.cpp game/entities/player/TelegraphedAbility.h game/entities/player/TelegraphedAttack.cpp game/entities/player/TelegraphedAttack.h game/entities/player/BossBuilder.h game/entities/player/BossBuilder.cpp game/entities/player/AbilityPicker.cpp game/world/MusicPlayer.cpp game/world/MusicPlayer.h game/utils/Text.cpp game/utils/Text.hpp game/utils/PositionSize.hpp game/entities/player/Shopkeeper.cpp game/entities/player/Shopkeeper.hpp game/Inventory/Item2.cpp game/Inventory/Item2.hpp game/entities/player/Sprites.cpp game/entities/player/Sprites.h game/utils/LingeringText.cpp game/utils/LingeringText.hpp game/world/Message.cpp game/world/Message.hpp game/world/Map.cpp game/world/Map.hpp game/world/MapTile.cpp game/world/MapTile.hpp game/entities/player/Pickup.cpp game/entities/player/Pickup.hpp game/entities/player/PickupFunctions.hpp game/entities/player/PickupItems.h game/world/OneWay.cpp game/world/OneWay.hpp game/world/LockedWall.cpp)

target_link_libraries(waifu ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARY} ${SDL2TTF_LIBRARIES} ${SDL2_GFX_LIBRARIES})


#target_link_libraries(waifu ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARY} Qt5::Widgets)
#target_link_libraries(waifu Qt5::Widgets)

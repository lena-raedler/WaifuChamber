cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")

project(waifu)

add_subdirectory(game)
include(FindPkgConfig)
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(waifu main.cpp game/game.cpp game/entities/player/player.cpp game/utils/renderer.cpp game/entities/player/Movable.cpp)

target_link_libraries(waifu ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

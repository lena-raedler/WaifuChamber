include(FindPkgConfig)
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_library(libGame game.cpp entities/player/statuseffect.cpp entities/player/statuseffect.h utils/triangle.cpp utils/triangle.h entities/player/Projectile.cpp entities/player/Interactable.h)
add_subdirectory(entities/player)
add_subdirectory(utils)
add_subdirectory(world)
target_include_directories (libGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

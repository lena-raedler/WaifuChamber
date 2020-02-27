include(FindPkgConfig)

find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})


add_library(libUtils renderer.cpp Vec2.h InputManager.cpp InputManager.h KeyboardMapping.h utility.h CollisionTree.cpp CollisionTree.h utility.cpp triangle.cpp triangle.h blackmagic.h LingeringText.cpp LingeringText.hpp)

target_include_directories (libUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

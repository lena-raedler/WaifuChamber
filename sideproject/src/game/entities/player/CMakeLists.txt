include(FindPkgConfig)

find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})


add_library(libPlayer player.cpp)

target_include_directories (libPlayer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# QT Widget
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(FindPkgConfig)
find_package(SDL2 REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_library(libGame game.cpp entities/player/statuseffect.cpp entities/player/statuseffect.h utils/triangle.cpp utils/triangle.h entities/player/Projectile.cpp entities/player/Interactable.h utils/blackmagic.h GlobalConstants.h GlobalConstants.cpp GlobalConstants.h SavedVariables.cpp SavedVariables.h)
add_subdirectory(entities/player)
add_subdirectory(utils)
add_subdirectory(world)
target_include_directories (libGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories (libGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Qt5::Widgets)
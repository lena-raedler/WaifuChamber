cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
#set(CMAKE_CXX_FLAGS "-Wall -I/home/bnorb/anaconda3/include/freetype2 -I/usr/include/SDL2 -D_REENTRANT -lSDL2 ${CMAKE_CXX_FLAGS} ")
#set(CMAKE_PREFIX_PATH "/usr/local/include/SDL2")
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")



# QT Widget
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

project(executable)

#add_subdirectory(game)
include(FindPkgConfig)
find_package(PkgConfig)

# the `pkg_check_modules` function is created with this call
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SDL2 REQUIRED sdl2)

find_package(SDL2 REQUIRED)
#find_package(SDL2_ttf REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
#PKG_SEARCH_MODULE(SDL2_ttf REQUIRED)
find_library(SDL_MIXER_LIBRARY
        NAMES SDL2_mixer
        HINTS
        ENV SDLMIXERDIR
        ENV SDLDIR
        PATH_SUFFIXES lib
        SDL2
        )



include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIR})

add_executable(executable 16_true_type_fonts.cpp lazy.ttf)

target_link_libraries(executable ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARY} ${SDL2TTF_LIBRARIES})
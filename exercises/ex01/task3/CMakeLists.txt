cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
#set(CMAKE_BUILD_TYPE Release)         # PS: Check if build type is already set and if not set it to release.
#set(CMAKE_CXX_FLAGS_DEBUG -Wall)
#set(CMAKE_CXX_FLAGS_DEBUG -Werror)
#set(CMAKE_CXX_FLAGS_DEBUG -graphviz=foo)
set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")

# CMAKE_CXX_FLAGS = "-Wall -Werror " + CMAKE_CXX_FLAGS

project(app)                          # Create project "app"

add_subdirectory(app)
add_subdirectory(libBar)
add_subdirectory(libBaz)
add_subdirectory(libFoo)
cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG -Wall)
set(CMAKE_CXX_FLAGS_DEBUG -Werror)
set(CMAKE_CXX_FLAGS_DEBUG -graphviz=foo)

project(app)                          # Create project "app"

add_subdirectory(app)
add_subdirectory(libBar)
add_subdirectory(libBaz)
add_subdirectory(libFoo)
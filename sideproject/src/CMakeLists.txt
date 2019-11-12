cmake_minimum_required(VERSION 3.10)  # CMake version check
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")

project(waifu)

add_subdirectory(game)


add_executable(waifu main.cpp)

target_link_libraries(waifu LINK_PUBLIC libGame libPlayer libUtil)

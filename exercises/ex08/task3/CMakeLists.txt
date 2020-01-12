cmake_minimum_required(VERSION 3.8)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_library(MyVector SHARED MyVector.cpp)
#target_include_directories(MyVector PUBLIC libMyVector)

add_executable(main demo.cpp)
#target_link_libraries(main MyVector)

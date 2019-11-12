
add_library(libGame game.cpp)
add_subdirectory(entities/player)
add_subdirectory(utils)
target_include_directories (libGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(libFoo foo.cpp)

target_include_directories (libFoo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
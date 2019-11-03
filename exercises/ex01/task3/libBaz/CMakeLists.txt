add_library(libBaz baz.cpp)

target_include_directories (libBaz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
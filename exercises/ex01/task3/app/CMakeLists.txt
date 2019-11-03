add_executable(app app.cpp)

target_link_libraries (app LINK_PUBLIC libBar libBaz libFoo)
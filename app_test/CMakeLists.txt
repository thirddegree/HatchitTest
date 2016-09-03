cmake_minimum_required(VERSION 3.5)

add_executable(apptest
        apptest.cpp)

target_link_libraries(apptest HatchitCore HatchitGraphics HatchitGame)
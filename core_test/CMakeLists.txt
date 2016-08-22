cmake_minimum_required(VERSION 3.5)

add_executable(RunCoreTests
                            INITest.cpp
                            JsonTest.cpp
                            OSTest.cpp)

target_link_libraries(RunCoreTests gtest gtest_main)
target_link_libraries(RunCoreTests HatchitCore)
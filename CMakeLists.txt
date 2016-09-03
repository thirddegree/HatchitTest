cmake_minimum_required(VERSION 3.5)

project(HatchitTest)

add_subdirectory(googletest)
add_subdirectory(core_test)
add_subdirectory(app_test)

set_target_properties(RunAppTest RunCoreTests gmock gmock_main gtest gtest_main PROPERTIES FOLDER Test)

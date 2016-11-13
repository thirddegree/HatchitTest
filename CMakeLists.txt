cmake_minimum_required(VERSION 3.5)

project(HatchitTest)

add_subdirectory(googletest)
add_subdirectory(core_test)
add_subdirectory(app_test)
add_subdirectory(network_test)

set_target_properties(RunAppTest RunCoreTests Server Client gmock gmock_main gtest gtest_main PROPERTIES FOLDER Test)

cmake_minimum_required(VERSION 3.5)

add_executable(RunAppTest
        apptest.cpp)

target_link_libraries(RunAppTest HatchitCore HatchitGraphics HatchitGame)

set_target_properties(RunAppTest
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	

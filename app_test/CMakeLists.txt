cmake_minimum_required(VERSION 3.5)

if(WIN32)

	if(BUILD_WINRT)
		add_executable(app_test WIN32 apptest.cpp)

		set_source_files_properties("apptest.cpp"
									PROPERTIES COMPILE_FLAGS /ZW)

		target_include_directories(app_test
			PUBLIC
			"${CMAKE_SOURCE_DIR}/HatchitCore/include"
			"${CMAKE_SOURCE_DIR}/HatchitCore/include/winrt"
			"${CMAKE_SOURCE_DIR}/HatchitCore/source/inline"
			"${CMAKE_SOURCE_DIR}/HatchitRuntime/include"
			"${CMAKE_SOURCE_DIR}/HatchitRuntime/include/winrt")
		target_link_libraries(app_test HatchitCore HatchitRuntime)
		set_target_properties(app_test PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:\"vccorlibd\" /NODEFAULTLIB:\"msvcrtd\" vccorlibd.lib msvcrtd.lib")
		set_target_properties(app_test PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:\"vccorlib\" /NODEFAULTLIB:\"msvcrt\" vccorlib.lib msvcrt.lib")
	else()
		add_executable(app_test WIN32
			apptest.cpp)

		target_link_libraries(app_test HatchitCore SDL2 SDL2main)
	endif()
endif()

set_target_properties(app_test
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	

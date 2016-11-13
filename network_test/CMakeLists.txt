cmake_minimum_required(VERSION 3.5)

add_executable(Server
        server.cpp)
add_executable(Client
        client.cpp)

target_link_libraries(Server HatchitCore HatchitNetwork)
target_link_libraries(Client HatchitCore HatchitNetwork)

set_target_properties(Server Client
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

cmake_minimum_required(VERSION 3.5)

file(GLOB PROTO_INC ${CMAKE_CURRENT_SOURCE_DIR}/*.pb.h)
file(GLOB PROTO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.pb.cc)
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

add_executable(Server
        server.cpp ${PROTO_INC} ${PROTO_SRC} ${PROTO_FILES})
add_executable(Client
        client.cpp ${PROTO_INC} ${PROTO_SRC} ${PROTO_FILES})

find_package(Protobuf REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${PROTOBUF_INCLUDE_DIR})

target_link_libraries(Server HatchitCore HatchitNetwork ${PROTOBUF_LIBRARY})
target_link_libraries(Client HatchitCore HatchitNetwork ${PROTOBUF_LIBRARY})

set_target_properties(Server Client
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_custom_command(TARGET Server
        PRE_BUILD
        COMMAND protoc -I=${CMAKE_CURRENT_SOURCE_DIR}/ --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/*.proto
        )

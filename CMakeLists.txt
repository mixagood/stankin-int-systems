cmake_minimum_required(VERSION 2.8)

project (stankin-iaes-labs)

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB Graph.cpp State.cpp)

add_library(Graph STATIC ${SOURCE_LIB})

add_library(State STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main Graph State)
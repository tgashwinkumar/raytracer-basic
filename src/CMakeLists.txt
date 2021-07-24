cmake_minimum_required(VERSION 3.10)

project(RaytracerBasic VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

message(STATUS "Project Binary dir:= ${CMAKE_BINARY_DIR}")
message(STATUS "Runtime Output Dir:= ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Library Output Dir:= ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

add_executable(${CMAKE_PROJECT_NAME} RaytracerBasic.cpp)
configure_file(RaytracerBasicConfig.h.in ../src/RaytracerBasicConfig.h)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC  "${PROJECT_BINARY_DIR}" )
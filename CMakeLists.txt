cmake_minimum_required(VERSION 3.10)

project(RaytracerBasic VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

include_directories("include")

add_executable(${CMAKE_PROJECT_NAME} ./src/main.cpp ./include/Vec3/vec3.h ./include/Vec3/color.h)
message("Project source dir:=${PROJECT_SOURCE_DIR}" )

configure_file(./src/RaytracerBasicConfig.h.in ./src/RaytracerBasicConfig.h)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC  
                                "${PROJECT_BINARY_DIR}"
                                )
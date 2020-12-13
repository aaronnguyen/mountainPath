cmake_minimum_required(VERSION 3.17)
project(mountainPath)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)
add_executable(PathFinding_run ${SOURCE_FILES})

include_directories(PathFinding_lib)
add_subdirectory(PathFinding_lib)

target_link_libraries(PathFinding_run PathFinding_lib)

add_subdirectory(GTest)

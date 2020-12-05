cmake_minimum_required(VERSION 3.17)
project(mountainPath)

set(CMAKE_CXX_STANDARD 20)

add_executable(mountainPath main.cpp generate_grid.cpp generate_grid.h shortestPath.cpp shortestPath.h)
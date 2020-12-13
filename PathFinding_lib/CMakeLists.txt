project(PathFinding)

set(HEADER_FILES generate_grid.h shortestPath.h)

set(SOURCE_FILES generate_grid.cpp shortestPath.cpp)

add_library(PathFinding_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
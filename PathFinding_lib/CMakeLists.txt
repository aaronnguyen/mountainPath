project(PathFinding)

set(HEADER_FILES generate_grid.h dijkstra.h)

set(SOURCE_FILES generate_grid.cpp dijkstra.cpp)

add_library(PathFinding_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
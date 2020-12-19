project(PathFinding)

set(HEADER_FILES generate_grid.h dijkstra.h bellmanFord.h)

set(SOURCE_FILES generate_grid.cpp dijkstra.cpp bellmanFord.cpp)

add_library(PathFinding_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
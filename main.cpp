#include <iostream>
#include <unordered_map>
#include <vector>

#include "generate_grid.h"
#include "shortestPath.h"

using namespace std;

int main() {
    generate_grid gg;

//    gg.display_data();

    shortPathBellmanFord bf;
    bf.BellmanFordAlgorithm(gg.costMapGrid, gg.startPoint, gg.endPoint);


   return 0;
}

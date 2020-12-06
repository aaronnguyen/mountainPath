#include <iostream>
#include <unordered_map>
#include <vector>
#include "generate_grid.h"
#include "shortestPath.h"

using namespace std;

int main() {

    string mode;
//    mode = "cin";
    mode = "hardcode";
//    mode = "random";

    costGrid dataGrid;

    if (mode == "cin"){
        generate_grid gg(true);
        dataGrid = gg.getGridData().specific;
    }
    else if (mode == "random"){
        generate_grid gg(false);
        gridData gd = gg.getGridData();

        unordered_map<int, costGrid> gd_assorted = gd.assorted;

        int amtKey = 50;
        auto gridSearch = gd_assorted.find(amtKey);
        if(gridSearch == gd_assorted.end()) {
            cout << "No Grid found at key: " << amtKey << "\n";
            return -1;
        }
        dataGrid = gridSearch->second;
    }
    else if (mode == "hardcoded"){

        unordered_map<char, int> cellKeyVals;
        cellKeyVals['f'] = 3;
        cellKeyVals['g'] = 1;
        cellKeyVals['G'] = 2;
        cellKeyVals['h'] = 4;
        cellKeyVals['m'] = 7;
        cellKeyVals['r'] = 5;

        vector<vector<char>> terrainMapGrid =
                {{'G', 'r', 'g', 'g', 'm', 'm', 'm', 'r', 'f', 'm'},
                 {'G', 'g', 'r', 'G', 'G', 'G', 'G', 'm', 'f', 'h'},
                 {'m', 'r', 'f', 'm', 'm', 'f', 'G', 'r', 'h', 'h'},
                 {'G', 'm', 'G', 'f', 'h', 'r', 'g', 'm', 'g', 'g'},
                 {'g', 'g', 'g', 'm', 'h', 'm', 'h', 'f', 'm', 'f'},
                 {'h', 'r', 'g', 'f', 'f', 'f', 'g', 'h', 'r', 'h'},
                 {'m', 'G', 'f', 'r', 'm', 'm', 'G', 'r', 'g', 'f'},
                 {'m', 'r', 'h', 'h', 'h', 'h', 'G', 'm', 'm', 'r'},
                 {'r', 'r', 'g', 'f', 'G', 'r', 'r', 'm', 'f', 'r'},
                 {'G', 'g', 'r', 'g', 'g', 'r', 'h', 'm', 'm', 'r'}};

        dataGrid.start = make_pair(0, 0);
        dataGrid.end = make_pair(7, 6);

        dataGrid.grid = convertTerrainToCostGrid(terrainMapGrid, cellKeyVals);

    }
    else return -1;

    display_data(dataGrid);
    cout << "\n\n";
    bellmanFord bf;
    shortRoute sr = bf.shortPath(dataGrid.grid, dataGrid.start, dataGrid.end);

    printShortRoute(sr);

    return 0;
}

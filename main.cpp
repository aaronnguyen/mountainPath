#include <iostream>
#include <unordered_map>
#include <vector>
#include "generate_grid.h"
//#include "shortestPath.h"
#include "dijkstra.h"


using namespace std;

int main() {

    string mode;
//    mode = "cin";
//    mode = "hardcode";
    mode = "assorted";

    costGrid dataGrid;

    if (mode == "cin"){
        generate_grid gg(true);
        dataGrid = gg.getGridData().specific;

        dijkstra searchAlgo;
        shortRoute sr = searchAlgo.shortPath(dataGrid.grid, dataGrid.start, dataGrid.end);
        printShortRoute(sr);
    }

    else if (mode == "assorted"){
        generate_grid gg(false);
        gridData gd = gg.getGridData();

        unordered_map<int, costGrid> gd_assorted = gd.assorted;

        dijkstra searchAlgo;

        for (int amtKey: {10, 20, 50, 200, 500, 1000}){
            auto gridSearch = gd_assorted.find(amtKey);
            if(gridSearch == gd_assorted.end()) {
                cout << "No Grid found at key: " << amtKey << "\n";
                return -1;
            }
            dataGrid = gridSearch->second;
            shortRoute sr = searchAlgo.shortPath(
                    dataGrid.grid, dataGrid.start, dataGrid.end);
            printShortRoute(sr);
        }
    }

    else if (mode == "hardcode"){

        unordered_map<char, int> cellKeyVals;
        cellKeyVals['f'] = 3;
        cellKeyVals['g'] = 1;
        cellKeyVals['G'] = 2;
        cellKeyVals['h'] = 4;
        cellKeyVals['m'] = 7;
        cellKeyVals['r'] = 5;

        vector<vector<char>> terrainMapGrid =
                {{'G', 'r', 'g', 'g'},
                 {'G', 'g', 'r', 'G'},
                 {'m', 'r', 'f', 'm'},
                 {'G', 'g', 'r', 'g'}};

        dataGrid.start = make_pair(0, 0);
        dataGrid.end = make_pair(3, 3);
        dataGrid.grid = convertTerrainToCostGrid(terrainMapGrid, cellKeyVals);
        dataGrid.rowCount = terrainMapGrid.size();
        dataGrid.colCount = terrainMapGrid[0].size();

        display_data(dataGrid);
        cout << "\n";

//    bellmanFord searchAlgo;
        dijkstra searchAlgo;

        shortRoute sr = searchAlgo.shortPath(dataGrid.grid, dataGrid.start, dataGrid.end);
        printShortRoute(sr);


    }
    else {
        string errorString = "Mode does not exist: " + mode;
        throw invalid_argument(errorString);
        return -1;
    }



    return 0;
}

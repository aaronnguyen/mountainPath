#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <algorithm>

#include "generate_grid.h"
//#include "bellmanFord.h"
#include "dijkstra.h"
//#include "primm.h"
//#include "kruskal.h"
//#include "astar.h"


using namespace std;

int main() {

    string mode;
//    mode = "cin";
    mode = "hardcode";
//    mode = "assorted";
    string algorithm;
    algorithm = "dijkstra";
    costGrid dataGrid;

    auto runAlgorithm = [](costGrid dataGrid, string algorithm) -> shortRoute {


        if (algorithm == "dijkstra"){
            return dijkstraShortPath(dataGrid.grid, dataGrid.start, dataGrid.end);
        }
        else if (algorithm == "bellmanford"){

        }

        return shortRoute();
    };


    auto runFromAssorted = [&runAlgorithm, algorithm](unordered_map<int, costGrid> &gd_assorted, int amtKey) -> int {

        cout << "=== Starting " << amtKey << " ===\n";
        auto gridSearch = gd_assorted.find(amtKey);
        if(gridSearch == gd_assorted.end()) {
            cout << "No Grid found at key: " << amtKey << "\n";
            return -1;
        }
        costGrid dataGrid = gridSearch->second;
//        shortRoute sr = dijkstraShortPath(
//                dataGrid.grid, dataGrid.start, dataGrid.end);
        shortRoute sr = runAlgorithm(dataGrid, algorithm);

        printShortRoute(sr);

        cout << "\n=== Completed " << amtKey << " ===\n";

        return 0;
    };

    if (mode == "cin"){
        generate_grid gg(true);
        dataGrid = gg.getGridData().specific;

//        shortRoute sr = dijkstraShortPath(dataGrid.grid, dataGrid.start, dataGrid.end);
        shortRoute sr = runAlgorithm(dataGrid, algorithm);

        printShortRoute(sr);
    }

    else if (mode == "assorted"){
        generate_grid gg(false);
        gridData gd = gg.getGridData();

        unordered_map<int, costGrid> gd_assorted = gd.assorted;

        vector<int> amtKeys = {10, 20, 50, 200, 500, 1000};
        vector<int> timeTaken;
        for (int ak: amtKeys){
            auto start = std::chrono::high_resolution_clock::now();
            
            int status = runFromAssorted(gd_assorted, ak);
            if (status < 0) return status;

            auto stop = std:: chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop-start);
            timeTaken.emplace_back(duration.count());

        }

        for (int i = 0; i < timeTaken.size(); ++i){
            cout << "Time (" << amtKeys[i] << " items) :: " << timeTaken[i] << " ms\n";
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
        dataGrid.end = make_pair(9, 9);
        dataGrid.grid = convertTerrainToCostGrid(terrainMapGrid, cellKeyVals);
        dataGrid.rowCount = terrainMapGrid.size();
        dataGrid.colCount = terrainMapGrid[0].size();

        display_data(dataGrid);
        cout << "\n";

//        shortRoute sr = dijkstraShortPath(dataGrid.grid, dataGrid.start, dataGrid.end);
        shortRoute sr = runAlgorithm(dataGrid, algorithm);
        printShortRoute(sr);

    }
    else {
        string errorString = "Mode does not exist: " + mode;
        throw invalid_argument(errorString);
    }

    return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <sstream>

#include "generate_grid.h"
#include "dijkstra.h"
#include "bellmanFord.h"


using namespace std;

void printShortRoute(vector<pair<int,int>> &routeGuidance, int &routeCost) {

    cout << routeCost << "\n";

    for (auto s: routeGuidance){
        cout << s.first << " " << s.second << "\n";
    }
}

int main(int argc, char** argv)  {

    costGrid dataGrid;

    auto runAlgorithm = [](int amtKey) -> void {

        generate_grid gg;
        costGrid dataGrid;
        if (amtKey == -1)
            dataGrid = gg.input_capture();
        else
            dataGrid = gg.generateRandomGrid(amtKey);

//        dijkstra sp;
        bellmanFord sp;

        sp.calculatePath(dataGrid.grid, dataGrid.start, dataGrid.end);

        vector<pair<int,int>> routeGuidance = sp.getRoute();
        int routeCost = sp.getCost();
        printShortRoute(routeGuidance, routeCost);

    };

//    vector<int> amtKeys = {10, 20, 50, 200, 500, 1000};
    int amtKey;

    int argvCount = 0;
    while(argv[++argvCount] != NULL);

    if (argvCount > 1){
        stringstream argstream(argv[1]);
        argstream >> amtKey;
    }
    else
        cout << "No args found, defaulting to 10.\n";
        amtKey = 10;

    auto start = std::chrono::high_resolution_clock::now();

    runAlgorithm(amtKey);

    auto stop = std:: chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop-start);

    cout << "\nTime (" << amtKey << " items) :: " << duration.count() << " ms\n";

    return 0;
}

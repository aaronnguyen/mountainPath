#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "generate_grid.h"
#include "dijkstra.h"

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

        dijkstra sp;
        sp.calculatePath(dataGrid.grid, dataGrid.start, dataGrid.end);

        vector<pair<int,int>> routeGuidance = sp.getRoute();
        int routeCost = sp.getCost();
        printShortRoute(routeGuidance, routeCost);

    };

//    vector<int> amtKeys = {10, 20, 50, 200, 500, 1000};
    int amtKey;
    stringstream argstream(argv[1]);
    argstream >> amtKey;

    auto start = std::chrono::high_resolution_clock::now();

    runAlgorithm(amtKey);

    auto stop = std:: chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop-start);

    cout << "\nTime (" << amtKey << " items) :: " << duration.count() << " ms\n";

    return 0;
}

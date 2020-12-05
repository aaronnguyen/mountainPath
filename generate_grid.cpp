//
// Created by aaronnguyen on 12/3/20.
//

#include "generate_grid.h"
#include <vector>
#include <iostream>

generate_grid::generate_grid(
        unordered_map<char, int> inputCellKeyVals, vector<vector<char>> inputTerrainMap) {

    generate_grid::cellKeyVals = inputCellKeyVals;
    generate_grid::terrainMapGrid = inputTerrainMap;
    generate_grid::convertTerrainToCostGrid();
}

generate_grid::generate_grid() {
    generate_grid::input_capture();
    generate_grid::convertTerrainToCostGrid();
}

void generate_grid::convertTerrainToCostGrid() {

    int rLen = terrainMapGrid.size();
    vector<vector<int>> costGrid(rLen, vector<int>());

    for(int i = 0; i < rLen; i++){
        vector<char> terrainRow = terrainMapGrid[i];
        for(char cell: terrainRow){
            auto search = cellKeyVals.find(cell);
            costGrid[i].emplace_back(search->second);
        }
    }

    costMapGrid = costGrid;

}

void generate_grid::input_capture() {

    int keyAmount;
    cin >> keyAmount;

    char charKey;
    int keyVal;

    // private: unordered_map<char, int> cellKeyVals;
    for (int i = 0; i < keyAmount; i++){
        cin >> charKey >> keyVal;
        cellKeyVals[charKey] = keyVal;
    }

    int rowAmt, colAmt;
    cin >> rowAmt >> colAmt;

    // private:  vector<vector<char>> terrainMapGrid;
    terrainMapGrid = vector(rowAmt, vector<char>(colAmt, '0'));

    char inCharVal;
    for(int i = 0; i < rowAmt; i++){
        for(int j = 0; j < colAmt; j++){
            cin >> inCharVal;
            terrainMapGrid[i][j] = inCharVal;
        }
    }

    // private:
    //    pair<int,int> startPoint;
    //    pair<int,int> endPoint;
    int startX, startY, endX, endY;
    cin >> startX >> startY;
    cin >> endX >> endY;
    startPoint = make_pair(startX, startY);
    endPoint = make_pair(endX, endY);

}

void generate_grid::display_data() {
    cout << "Start: (" << startPoint.first << "," << startPoint.second << ")\n";
    cout << "End: (" << endPoint.first << "," << endPoint.second << ")\n";

    cout << "TerrainMap in Cost form: \n";
    for(auto i: costMapGrid){
        for(auto cell: i){
            cout << cell << " ";
        }
        cout << "\n";
    }

}

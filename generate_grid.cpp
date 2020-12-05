//
// Created by aaronnguyen on 12/3/20.
//

#include "generate_grid.h"
#include <vector>

generate_grid::generate_grid(
        unordered_map<char, int> inputCellKeyVals, vector<vector<char>> inputTerrainMap) {
    generate_grid::cellKeyVals = inputCellKeyVals;
    generate_grid::terrainMapGrid = inputTerrainMap;
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

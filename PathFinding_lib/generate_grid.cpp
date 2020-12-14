//
// Created by aaronnguyen on 12/3/20.
//

#include "generate_grid.h"
#include <vector>
#include <iostream>
#include <random>

generate_grid::generate_grid() {}

costGrid generate_grid::input_capture() {

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

    int startX, startY, endX, endY;
    cin >> startX >> startY;
    cin >> endX >> endY;

    // format the data to be distributed.
    costGrid cg = convertTerrainToCostGrid(terrainMapGrid, cellKeyVals);
    cg.rowCount = rowAmt;
    cg.colCount = colAmt;
    cg.start = make_pair(startX, startY);
    cg.end = make_pair(endX, endY);

    return cg;
}

costGrid generate_grid::generateRandomGrid(int amt) {

    //create nxn grids with assorted numbers. going to use 2 digit numbers

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution dist(10, 99);

    vector<vector<int>> r;
    for (int i = 0; i < amt; ++i){
        vector<int> t;
        for (int j = 0; j < amt; ++j){
            t.emplace_back(dist(mt));
        }
        r.emplace_back(t);
    }

    costGrid tempCG;
    tempCG.rowCount = r.size();
    if (tempCG.rowCount == 0) tempCG.colCount = 0;
    else tempCG.colCount = r[0].size();
    tempCG.grid = r;


    uniform_int_distribution coordDist(0, amt-1);
//    tempCG.start = make_pair(coordDist(mt), coordDist(mt));
//    tempCG.end = make_pair(coordDist(mt), coordDist(mt));
    tempCG.start = make_pair(0,0);
    tempCG.end = make_pair(amt-1, amt-1);
    return tempCG;
}

costGrid convertTerrainToCostGrid(
        vector<vector<char>> &terrainMapGrid,
        unordered_map<char, int> &cellKeyVals) {

    int rLen = terrainMapGrid.size();
    vector<vector<int>> grid(rLen, vector<int>());

    for(int i = 0; i < rLen; i++){
        vector<char> terrainRow = terrainMapGrid[i];
        for(char cell: terrainRow){
            auto search = cellKeyVals.find(cell);
            grid[i].emplace_back(search->second);
        }
    }

    costGrid cg;
    cg.grid = grid;
    cg.rowCount = grid.size();

    if (cg.rowCount == 0) cg.colCount = 0;
    else cg.colCount = grid[0].size();
    // assuming it is a rectangular grid.

    return cg;
}

void display_data(
        pair<int,int> start, pair<int,int> end,
        pair<int, int> dimensions, vector<vector<int>> cg) {
    cout << "Start: (" << start.first << "," << start.second << ")\n";
    cout << "End: (" << end.first << "," << end.second << ")\n";

    cout << "Dimensions: R" << dimensions.first << " x C" << dimensions.second << "\n";
    cout << "TerrainMap in Cost form: \n";
    for(auto row: cg){
        for(auto cell: row){
            cout << cell << " ";
        }
        cout << "\n";
    }

}

void display_data(costGrid cg) {
    display_data(cg.start, cg.end, make_pair(cg.rowCount, cg.colCount), cg.grid);
}

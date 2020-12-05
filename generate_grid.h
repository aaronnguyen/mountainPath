//
// Created by aaronnguyen on 12/3/20.
//

#ifndef MOUNTAINPATH_GENERATE_GRID_H
#define MOUNTAINPATH_GENERATE_GRID_H

#include <vector>
#include <unordered_map>
using namespace std;

class generate_grid{
private:
    unordered_map<char, int> cellKeyVals;
    vector<vector<char>> terrainMapGrid;
    vector<vector<int>> costMapGrid;

    void convertTerrainToCostGrid();

public:
    generate_grid(unordered_map<char, int> cellKeyVals, vector<vector<char>> terrainMap);

};

#endif //MOUNTAINPATH_GENERATE_GRID_H


//Note: from Main
//unordered_map<char, int> charValMap;
//vector<vector<char>> generate_grid(row, vector<char>(col, '0'));
//
//int startX, startY, endX, endY;

//
// Created by aaronnguyen on 12/3/20.
//

#ifndef MOUNTAINPATH_GENERATE_GRID_H
#define MOUNTAINPATH_GENERATE_GRID_H

#include <vector>
#include <unordered_map>
using namespace std;

struct costGrid{
    vector<vector<int>> grid;
    int rowCount;
    int colCount;
    pair<int,int> start;
    pair<int,int> end;
};

costGrid convertTerrainToCostGrid(
        vector<vector<char>> &terrainMapGrid, unordered_map<char, int> &cellKeyVals);

void display_data(pair<int,int> start, pair<int,int> end, vector<vector<int>> cg);
void display_data(costGrid cg);

class generate_grid{
private:
    unordered_map<char, int> cellKeyVals;
    vector<vector<char>> terrainMapGrid;

public:
    explicit generate_grid();
    costGrid input_capture();
    static costGrid generateRandomGrid(int amt);
};

#endif //MOUNTAINPATH_GENERATE_GRID_H


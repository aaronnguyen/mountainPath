//
// Created by aaronnguyen on 12/3/20.
//

#ifndef MOUNTAINPATH_SHORTESTPATH_H
#define MOUNTAINPATH_SHORTESTPATH_H

#include <vector>
#include <unordered_map>
using namespace std;

pair<vector<vector<int>>,int> calculateShortRouteAndCost(
        unordered_map<char, int> &cellKeyVals,
        vector<vector<char>> &terrainMapGrid,
        pair<int,int> start, pair<int,int> end
        );
pair<vector<vector<int>>,int> calculateShortRouteAndCost(
        vector<vector<int>> &costMapGrid,
        pair<int,int> start, pair<int,int> end
        );


#endif //MOUNTAINPATH_SHORTESTPATH_H

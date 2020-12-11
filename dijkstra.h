//
// Created by aaronnguyen on 12/8/20.
//

#ifndef MOUNTAINPATH_DIJKSTRA_H
#define MOUNTAINPATH_DIJKSTRA_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "dijkstra.h"
using namespace std;

struct shortRoute{
    vector<pair<int,int>> routeGuidance;
    int routeCost;
};

void printShortRoute(shortRoute solution);


class dijkstra{
private:
    struct dNode{
        int weight;
        int index;
        int fromNode;
        pair<int,int> coordinate;
    };

    // vertex index value should correspond with the dNode.index
    vector<vector<dNode>> weightTable;
    vector<dNode> completedRoute;

public:
//    shortRoute shortPath(vector<vector<int>> &costMapGrid,
//                         pair<int,int> &start, pair<int,int> &end);

    shortRoute shortPath(vector<vector<int>> &costMapGrid,
                         pair<int, int> &start, pair<int, int> &end);

};







#endif //MOUNTAINPATH_DIJKSTRA_H

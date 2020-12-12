//
// Created by aaronnguyen on 12/8/20.
//

#ifndef MOUNTAINPATH_DIJKSTRA_H
#define MOUNTAINPATH_DIJKSTRA_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <bits/stdc++.h> // for INT_MAX
#include <sstream>

using namespace std;

struct shortRoute{
    vector<pair<int,int>> routeGuidance;
    int routeCost;
};

void printShortRoute(shortRoute solution);

shortRoute dijkstraShortPath(vector<vector<int>> &costMapGrid,
                             pair<int, int> &start, pair<int, int> &end);

#endif //MOUNTAINPATH_DIJKSTRA_H

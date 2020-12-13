//
// Created by aaronnguyen on 12/8/20.
//

#ifndef MOUNTAINPATH_SHORTESTPATH_H
#define MOUNTAINPATH_SHORTESTPATH_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <bits/stdc++.h> // for INT_MAX
#include <sstream>

using namespace std;

class shortestPath{
private:
    vector<pair<int,int>> routeGuidance;
    int routeCost;
public:
    void djikstra(vector<vector<int>> &costMapGrid,
                  pair<int, int> &start, pair<int, int> &end);

    vector<pair<int,int>> getRoute(){ return routeGuidance; }

    int getCost() const{ return routeCost; }
};



#endif //MOUNTAINPATH_SHORTESTPATH_H

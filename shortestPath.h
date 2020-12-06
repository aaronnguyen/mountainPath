//
// Created by aaronnguyen on 12/3/20.
//

#ifndef MOUNTAINPATH_SHORTESTPATH_H
#define MOUNTAINPATH_SHORTESTPATH_H

#include <vector>
#include <unordered_map>
using namespace std;

struct shortRoute{
    vector<pair<int,int>> routeGuidance;
    int routeCost;
};


class shortPathBellmanFord{
private:
    struct EDGE{
        pair<int, int> src;
        pair<int, int> dest;
        int weight;
    };

    shortRoute solution;

public:

    void BellmanFordAlgorithm(vector<vector<int>> &costMapGrid,
                              pair<int, int> start, pair<int, int> end);

    shortRoute getSolution() {
        return solution;
    }

};

//
//shortRoute calcRoute_dijkstra(
//        vector<vector<int>> &costMapGrid,
//        pair<int,int> start, pair<int,int> end
//);
//
//shortRoute calcRoute_primm(
//        vector<vector<int>> &costMapGrid,
//        pair<int,int> start, pair<int,int> end
//);
//
//shortRoute calcRoute_kruskal(
//        vector<vector<int>> &costMapGrid,
//        pair<int,int> start, pair<int,int> end
//);
//
//shortRoute calcRoute_aStar(
//        vector<vector<int>> &costMapGrid,
//        pair<int,int> start, pair<int,int> end
//);


#endif //MOUNTAINPATH_SHORTESTPATH_H

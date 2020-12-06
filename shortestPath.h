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

void printShortRoute(shortRoute solution);

class bellmanFord{
private:
    struct EDGE{
        int src;
        int dest;
        int weight;
    };
    struct coord{
        int x;
        int y;
        int idx;
    };

public:

    shortRoute shortPath(vector<vector<int>> &costMapGrid,
                              pair<int, int> start, pair<int, int> end);

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

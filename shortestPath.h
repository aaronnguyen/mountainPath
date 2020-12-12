//
// Created by aaronnguyen on 12/3/20.
//

#ifndef MOUNTAINPATH_SHORTESTPATH_H
#define MOUNTAINPATH_SHORTESTPATH_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

struct shortRoute{
    vector<pair<int,int>> routeGuidance;
    int routeCost;
};

void printShortRoute(shortRoute solution);

struct EDGE{
    int srcIdx;
    int destIdx;
    int weight;
};
struct COOR{
    int x;
    int y;
    int idx;
};

class bellmanFord{
//private:


public:

    shortRoute shortPath(vector<vector<int>> &costMapGrid,
                         pair<int, int> &start, pair<int, int> &end);

};

class dijkstra{
private:


public:
    shortRoute shortPath(vector<vector<int>> &costMapGrid,
                         pair<int,int> &start, pair<int,int> &end);
};


struct edgeNodeData{
    vector<EDGE> edges;
    unordered_map<int, vector<EDGE>> adj;
    unordered_map<string, COOR> nodeRef;
    int endIndex;
    unordered_map<int, COOR> nodRef_intIndex;
};

edgeNodeData travelEdgesBFS();



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

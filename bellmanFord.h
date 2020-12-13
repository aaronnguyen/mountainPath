//
// Created by aaronnguyen on 12/3/20.
//

#ifndef MOUNTAINPATH_BELLMANFORD_H
#define MOUNTAINPATH_BELLMANFORD_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

struct shortRoute{
    vector<pair<int,int>> routeGuidance;
    int routeCost;
};
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
struct edgeNodeData{
    vector<EDGE> edges;
    unordered_map<int, vector<EDGE>> adj;
    unordered_map<string, COOR> nodeRef;
    int endIndex;
    unordered_map<int, COOR> nodRef_intIndex;
};

class bellmanFord{

private:

    edgeNodeData edgeData;

    void generateEdgeList(vector<vector<int>> &costMapGrid,
                          pair<int, int> &start, pair<int, int> &end,
                          vector<int> border);
    bool calculatePaths(int vertextCount, int *parent, vector<int> &value);
    shortRoute drawRoute(int *parent, vector<int> &value);

public:

    shortRoute shortPath(vector<vector<int>> &costMapGrid,
                         pair<int, int> &start, pair<int, int> &end);

};

#endif //MOUNTAINPATH_BELLMANFORD_H

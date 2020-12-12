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

void printShortRoute(shortRoute solution);



class bellmanFord{
private:
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

    edgeNodeData generateEdgeList(vector<vector<int>> &costMapGrid,
                                  pair<int, int> &start, pair<int, int> &end,
                                  vector<int> border);

public:

    shortRoute shortPath(vector<vector<int>> &costMapGrid,
                         pair<int, int> &start, pair<int, int> &end);

};

#endif //MOUNTAINPATH_BELLMANFORD_H

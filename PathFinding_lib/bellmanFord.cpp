//
// Created by aaronnguyen on 12/3/20.
//

// TODO: cost is leaving the node, not the cost of entering the node. need to fix logic

#include "bellmanFord.h"
#include <bits/stdc++.h> // for INT_MAX

bool bellmanFord::calculatePath(vector<vector<int>> &costMapGrid,
                                  pair<int, int> &start, pair<int, int> &end){

    // define the boundaries.
    int minX = 0;
    int minY = 0;
    int maxX = costMapGrid.size();
    int maxY = costMapGrid[0].size();

    generateEdgeList(
            costMapGrid, start, end,
            {minX, minY, maxX, maxY});


    // Bellman Ford Path Search
    int vertexCount = edgeData.nodeRef.size();
    // private: vector<EDGE> edge;

    int parent[vertexCount];
    vector<int> value(vertexCount, INT_MAX);

    bool success = calculatePaths(vertexCount, parent, value);
    if (!success) return false;

    drawRoute(parent, value);
    return true;
}


void bellmanFord::generateEdgeList(vector<vector<int>> &costMapGrid,
                              pair<int, int> &start, pair<int, int> &end,
                              vector<int> border){

    vector<vector<int>> moveDir = {{0,1},{1,0},{0,-1},{-1,0}};

    // define the boundaries.
    int minX = border[0];
    int minY = border[1];
    int maxX = border[2];
    int maxY = border[3];

    // pair of ints to string. for key ref use.
    auto pts = [](int x, int y){
        return to_string(x) + "," + to_string(y);
    };

    auto inBounds = [minX, minY, maxX, maxY](int x, int y) -> bool {
        return x >= minX && x < maxX && y >= minY && y < maxY;
    };

    // BFS search through all nodes until we hit the end.
    // save that traversal into a vector and index of vector will be id of node
    // since Bellman Ford is only directed graphs, we can outline the possible edges
    // prior to running the search.
    queue<pair<int,int>> bfs;
    bfs.push(start);

    int endIdx = -1;

    vector<EDGE> edges;
    // used to store the coordinates of nodes, locatable by index number.

    // specific to Dijkstras
    unordered_map<int, vector<EDGE>> adj;
    // int should be the index of src node.
    // pair<int, int> == {weight, neighborVertexID}
    // edge contains all the data. just make it searchable by int.

    // nodeIdx to label the nodes with an int.
    // doesn't matter what order as long as we can reference it later.
    int nodeIdx = 0;
    unordered_map<string, COOR> nodeRef;
    unordered_map<int, COOR> nodRef_intIndex;

    COOR c;
    c.x = start.first;
    c.y = start.second;
    c.idx = nodeIdx;
    nodeRef[pts(c.x, c.y)] = c;

    while(!bfs.empty()){
        pair<int,int> curr = bfs.front();
        bfs.pop();
        int cx = curr.first;
        int cy = curr.second;
        string currKey = pts(cx, cy);
        int currIdx = nodeRef.find(currKey)->second.idx;

        for (auto m: moveDir){

            int nx = cx+m[0];
            int ny = cy+m[1];

            if (inBounds(nx, ny)){
                string newKey = pts(nx, ny);
                if (nodeRef.find(newKey) == nodeRef.end()) {
                    nodeIdx++;
                    COOR newCoord;
                    newCoord.x = nx;
                    newCoord.y = ny;
                    newCoord.idx = nodeIdx;

                    pair<int,int> newPair = make_pair(nx, ny);
                    if (newPair == end) endIdx = nodeIdx;

                    nodeRef[newKey] = newCoord;
                    nodRef_intIndex[nodeIdx] = newCoord;
                    bfs.push(newPair);
                }

                EDGE newEdge;
                newEdge.srcIdx = currIdx;
                newEdge.destIdx = nodeRef.find(newKey)->second.idx;
                newEdge.weight = costMapGrid[nx][ny];

                edges.emplace_back(newEdge);

                adj.insert({currIdx, vector<EDGE>()});
                adj[currIdx].emplace_back(newEdge);
            }
        }
    }

    edgeNodeData edd;

    edd.edges = edges;
    edd.nodeRef = nodeRef;
    edd.adj = adj;
    edd.endIndex = endIdx;
    edd.nodRef_intIndex = nodRef_intIndex;

    edgeData = edd;
}

bool bellmanFord::calculatePaths(int vertexCount, int *parent, vector<int> &value) {

    // Bellman Ford Path Search
    int edgeCount = edgeData.edges.size();
    // private: vector<EDGE> edge;


    // initialize vars
    parent[0] = -1;
    value[0] = 0;

    // control graph flow with bool
    bool updated;
    for (int i = 0; i < vertexCount-1; ++i){
        updated = false;
        for(int j = 0; j < edgeCount; ++j){
            int src_j = edgeData.edges[j].srcIdx;
            int dst_j = edgeData.edges[j].destIdx;
            int wgt_j = value[src_j] + edgeData.edges[j].weight;
            if (value[src_j] != INT_MAX && wgt_j < value[dst_j]){
                value[dst_j] = wgt_j;
                parent[dst_j] = src_j;
                updated = true;
            }
        }
        if (!updated) break;
    }

    // check for negative edge cycles
    for (int i = 0; i < edgeCount && updated; ++i){
        int src_negCheck = edgeData.edges[i].srcIdx;
        int dest_negCheck = edgeData.edges[i].destIdx;
        int weight_negCheck = edgeData.edges[i].weight;

        if (value[src_negCheck] != INT_MAX && value[src_negCheck] + weight_negCheck < value[dest_negCheck]) {
            cout << "Graph has a negative edge cycle\n";
            return false;
        }
    }

    return true;
}

void bellmanFord::drawRoute(int *parent, vector<int> &value) {
    // we built a reference, but now format it so we can use it.
    COOR coordByIndex[edgeData.nodeRef.size()];
    for (auto n: edgeData.nodeRef){
        COOR nc = n.second;
        coordByIndex[nc.idx] = nc;
    }

    // figure out shortest path by working backwards.
    int i = edgeData.endIndex;
    vector<pair<int,int>> routeGuide;
    do {
        routeGuide.emplace_back(make_pair(coordByIndex[i].x, coordByIndex[i].y));
        i = parent[i];
    } while(i != -1);

    reverse(routeGuide.begin(), routeGuide.end());

    routeCost = value[edgeData.endIndex];
    routeGuidance = routeGuide;
}

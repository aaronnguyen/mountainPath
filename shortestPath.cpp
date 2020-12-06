//
// Created by aaronnguyen on 12/3/20.
//

#include "shortestPath.h"
#include <bits/stdc++.h> // for INT_MAX

void printShortRoute(shortRoute solution) {

    cout << solution.routeCost << "\n";

    for (auto s: solution.routeGuidance){
        cout << s.first << " " << s.second << "\n";
    }
}

shortRoute bellmanFord::shortPath(vector<vector<int>> &costMapGrid,
                            pair<int, int> start, pair<int, int> end){

    vector<vector<int>> moveDir = {{0,1},{1,0}};
//    assuming that start is northWest of end.

//    BFS search through all nodes until we hit the end.
//    save that traversal into a vector and index of vector will be id of node
    queue<pair<int,int>> bfs;
    unordered_map<string, coord> nodeRef;
    vector<EDGE> edges;
    // used to store the coordinates of nodes, locatable by index number.

    auto pts = [](int x, int y){
        return to_string(x) + "," + to_string(y);
    };
    int nodeIdx = 0;
    bfs.push(start);
//    nodeRef.emplace_back(start);
    coord c;
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

            if (nx <= end.first && ny <= end.second){
                string newKey = pts(nx, ny);
                if (nodeRef.find(newKey) == nodeRef.end()) {
                    nodeIdx++;
                    coord newCoord;
                    newCoord.x = nx;
                    newCoord.y = ny;
                    newCoord.idx = nodeIdx;

                    nodeRef[newKey] = newCoord;
                    bfs.push(make_pair(nx, ny));
                }

                EDGE newEdge;
                newEdge.src = currIdx;
                newEdge.dest = nodeRef.find(newKey)->second.idx;
                newEdge.weight = costMapGrid[nx][ny];
                edges.emplace_back(newEdge);
            }
        }
    }

//    Bellman Ford Path Search
    int vertexCount = nodeRef.size();
    int edgeCount = edges.size();
//    vector<EDGE> edge;

    int parent[vertexCount];
    vector<int> value(vertexCount, INT_MAX);

    //initialize
    parent[0] = -1;
    value[0] = 0;

    // control graph flow with bool
    bool updated;
    for (int i = 0; i < vertexCount-1; ++i){
        updated = false;
        for(int j = 0; j < edgeCount; ++j){
            int src_j = edges[j].src;
            int dst_j = edges[j].dest;
            int wgt_j = value[src_j] + edges[j].weight;
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
        int src_negCheck = edges[i].src;
        int dest_negCheck = edges[i].dest;
        int weight_negCheck = edges[i].weight;

        if (value[src_negCheck] != INT_MAX && value[src_negCheck] + weight_negCheck < value[dest_negCheck]) {
            cout << "Graph has a negative edge cycle\n";
            return shortRoute();
        }
    }

    // we built a reference, but now format it so we can use it.
    coord coordByIndex[nodeRef.size()];
    for (auto n: nodeRef){
        coord nc = n.second;
        coordByIndex[nc.idx] = nc;
    }

    // figure out shortest path by working backwards.
    int optimalPath = vertexCount-1;
    vector<pair<int,int>> routeGuide;
//    cout << "Key: src --> dest :: cost\n";
//    cout << "NOTE: route in reverse\n=====\n";
    for (int i = vertexCount-1; i >= 0; --i){
//        cout << parent[i] << " --> " << i << " :: " << value[i] << "\n";

        if (i == optimalPath){
            routeGuide.emplace_back(make_pair(coordByIndex[i].x, coordByIndex[i].y));
            optimalPath = parent[i];
        }

    }

    reverse(routeGuide.begin(), routeGuide.end());
    shortRoute sr;
    sr.routeCost = value[vertexCount-1];
    sr.routeGuidance = routeGuide;
    return sr;

}


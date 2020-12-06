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

    vector<vector<int>> moveDir = {{0,1},{1,0},{0,-1},{-1,0}};
    
    // define the boundaries.
    int minX = 0;
    int minY = 0;
    int maxX = costMapGrid.size();
    int maxY = costMapGrid[0].size();

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

    // nodeIdx to label the nodes with an int.
    // doesn't matter what order as long as we can reference it later.
    int nodeIdx = 0;
    unordered_map<string, coord> nodeRef;
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

            if (inBounds(nx, ny)){
                string newKey = pts(nx, ny);
                if (nodeRef.find(newKey) == nodeRef.end()) {
                    nodeIdx++;
                    coord newCoord;
                    newCoord.x = nx;
                    newCoord.y = ny;
                    newCoord.idx = nodeIdx;

                    pair<int,int> newPair = make_pair(nx, ny);
                    if (newPair == end) endIdx = nodeIdx;

                    nodeRef[newKey] = newCoord;
                    bfs.push(newPair);
                }

                EDGE newEdge;
                newEdge.src = currIdx;
                newEdge.dest = nodeRef.find(newKey)->second.idx;
                newEdge.weight = costMapGrid[nx][ny];
                edges.emplace_back(newEdge);
            }
        }
    }

    // Bellman Ford Path Search
    int vertexCount = nodeRef.size();
    int edgeCount = edges.size();
    // private: vector<EDGE> edge;

    int parent[vertexCount];
    vector<int> value(vertexCount, INT_MAX);

    // initialize vars
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
    int i = endIdx;
    vector<pair<int,int>> routeGuide;
    do {
        routeGuide.emplace_back(make_pair(coordByIndex[i].x, coordByIndex[i].y));
        i = parent[i];
    } while(i != -1);

    reverse(routeGuide.begin(), routeGuide.end());
    shortRoute sr;
    sr.routeCost = value[endIdx];
    sr.routeGuidance = routeGuide;
    return sr;

}


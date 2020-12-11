//
// Created by aaronnguyen on 12/3/20.
//

// NOTE TO SELF: cost is leaving the node, not the cost of entering the node.

#include "shortestPath.h"
#include <bits/stdc++.h> // for INT_MAX

void printShortRoute(shortRoute solution) {

    cout << solution.routeCost << "\n";

    for (auto s: solution.routeGuidance){
        cout << s.first << " " << s.second << "\n";
    }
}

shortRoute bellmanFord::shortPath(vector<vector<int>> &costMapGrid,
                                  pair<int, int> &start, pair<int, int> &end){

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
    unordered_map<string, COOR> nodeRef;
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
                    bfs.push(newPair);
                }

                EDGE newEdge;
                newEdge.srcIdx = currIdx;
                newEdge.destIdx = nodeRef.find(newKey)->second.idx;
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
            int src_j = edges[j].srcIdx;
            int dst_j = edges[j].destIdx;
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
        int src_negCheck = edges[i].srcIdx;
        int dest_negCheck = edges[i].destIdx;
        int weight_negCheck = edges[i].weight;

        if (value[src_negCheck] != INT_MAX && value[src_negCheck] + weight_negCheck < value[dest_negCheck]) {
            cout << "Graph has a negative edge cycle\n";
            return shortRoute();
        }
    }

    // we built a reference, but now format it so we can use it.
    COOR coordByIndex[nodeRef.size()];
    for (auto n: nodeRef){
        COOR nc = n.second;
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


edgeNodeData generateEdgeList(vector<vector<int>> &costMapGrid,
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

    return edd;

}

shortRoute dijkstra::shortPath(vector<vector<int>> &costMapGrid,
                               pair<int, int> &start, pair<int, int> &end) {

    int maxX = costMapGrid.size();
    int maxY = costMapGrid[0].size();
    edgeNodeData edd = travelEdgesBFS(
            costMapGrid, start, end,
            {0,0,maxX, maxY});

    int pingcnt = 0;
    auto ping = [&pingcnt](){
        cout << "Ping (" << pingcnt << ")...\n";
        pingcnt++;
    };

    unordered_map<int, vector<EDGE>> adjacency = edd.adj;
//    unordered_map<int, pair<int,int>> adjacency;
    // pair<int, int> == {weight, neighborVertexID}
    priority_queue<pair<int, int>> pq;

    int vertextAmount; //vertextAmount
    bool processed[vertextAmount]; //visited

    int source = 0; // index to denote name of node.
    int accruedDist[vertextAmount];
    int fromParent[vertextAmount];
    for (int i = 0; i < vertextAmount; ++i){
        accruedDist[i] = INT_MAX;
        fromParent[i] = -1;
        processed[i] = false;
    }

    accruedDist[source] = 0;
    pq.push({0, source});

    while(!pq.empty()){

        pair<int, int> pqNode = pq.top();
        int srcIdx = pqNode.second; // vertext of interest, srcIdx
        pq.pop();

        cout << "EndIndex: " << edd.endIndex << "\n";
        cout << "Source: " << srcIdx << "\n";
        if(!processed[srcIdx] && srcIdx != edd.endIndex){

            cout << "nSIZE: " << adjacency[srcIdx].size() << "\n";
            for (auto neighbor: adjacency[srcIdx]){ //adjacency is an adjacency list; unordered_map
                ping();
                // srcIdx = src, destIdx == dest, destWeight = weight
                int destIdx = neighbor.destIdx; // node destIdx could be first, my choice
                int destWeight = neighbor.weight;

                cout << srcIdx << "," << destIdx << "\n";
                cout << accruedDist[srcIdx] + destWeight << " <? " << accruedDist[destIdx] << "\n";
                if(accruedDist[srcIdx] + destWeight < accruedDist[destIdx]) {
                    accruedDist[destIdx] = accruedDist[srcIdx] + destWeight;
                    pq.push({accruedDist[destIdx], destIdx});
                    fromParent[destIdx] = srcIdx;
                }
            }
            processed[srcIdx] = true;
        }
    }


//    Convert data into to shortRoute obj;
    shortRoute sr;

    vector<pair<int,int>> route;
    int seekIdx = edd.endIndex;
    do {
        cout << seekIdx << "<--" << fromParent[seekIdx] << "\n";
//        COOR n = edd.nodRef_intIndex[seekIdx];
//        route.emplace_back(make_pair(n.x, n.y));
        seekIdx = fromParent[seekIdx];

    } while (seekIdx > 0);
//    reverse(route.begin(), route.end());
//
    sr.routeCost = accruedDist[edd.endIndex];
    sr.routeGuidance = route;
    return sr;
}

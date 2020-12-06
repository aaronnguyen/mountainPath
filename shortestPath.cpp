//
// Created by aaronnguyen on 12/3/20.
//

#include "shortestPath.h"
#include <bits/stdc++.h> // for INT_MAX

//void shortPathBellmanFord::calculatePath_BellmanFord(
//        vector<vector<int>> &costMapGrid, pair<int, int> start, pair<int, int> end) {
//
////    setupEdgeList(costMapGrid);
//    BellmanFordAlgorithm(costMapGrid, start, end);
//
//}

//void shortPathBellmanFord::setupEdgeList(
//        vector<vector<int>> &costMapGrid) {
//
//    int minRow = 0, minCol = 0;
//    int maxRow = costMapGrid.size()-1, maxCol = costMapGrid[0].size()-1;
//    // make the max values aligned with the index values
//
//    vector<EDGE> t_edges;
//
//    // bfs queue
//    queue<EDGE> q;
//
//    EDGE root;
//    root.src = make_pair(-1, -1);
//    root.dest = make_pair(0,0);
//    root.weight = 0;
//    //no cost since we are not actually moving through it.
//
//    q.push(root);
//
//    while(!q.empty()){
//        EDGE curr = q.front();
//        q.pop();
//
//        auto cs = curr.src;
//        auto cd = curr.dest;
//        int cw = curr.weight;
//
//        vector<vector<int>> moveDir = { {0,1}, {1,0}, {0,-1}, {-1,0} };
//        for (auto d: moveDir){
//            int newX = curr.dest.first+d[0];
//            int newY = curr.dest.second+d[1];
//
//            if (newX >= minRow && newY <= minCol && newX <= maxRow && newY <= maxCol){
//                EDGE newEdge;
//                newEdge.src = cd;
//                newEdge.dest = make_pair(newX, newY);
//                newEdge.weight = costMapGrid[newX][newY];
//
//                q.push(newEdge);
//                t_edges.emplace_back(newEdge);
//            }
//        }
//    }
//    edges = t_edges;
//}


void shortPathBellmanFord::BellmanFordAlgorithm(
        vector<vector<int>> &costMapGrid,
        pair<int, int> start, pair<int, int> end){

    // Functor to convert pair of ints into string for key comparisons
    // pts = pair to string
    auto pts = [](int xIn, int yIn) -> string{
        return to_string(xIn) + "," + to_string(yIn);
    };

    // int Vertex and int Edges, Edges = Vertex-1.
    // using unordered_map, so we will keep track that way.
    unordered_map<string, string> parent;
    unordered_map<string, int> parentCost, value;
    // algo fills value up with INT_MAX, but just use existence as the INT_MAX

    vector<EDGE> edges;

    // set<string> visited;
    //Dont need to keep track of visited. we are already iterating through all nodes once.
    int vertexCount = 0;
    int edgeCount = 0;
    // using start and end coordinates to shrink zone down to relevant
    for (int i = start.first; i < end.first; ++i){
        for (int j = start.second; j < end.second; ++j){
            vertexCount++;

            int weight = costMapGrid[i][j];

            // Note: Bellman Ford is directional, so only moving in one direction.
            // i.e. can't move backwards.
            vector<vector<int>> moveDir = {{0,1}, {1,0}};
            for (auto m: moveDir){
                int nX = i+m[0];
                int nY = j+m[1];

                EDGE nEdge;
                nEdge.src = make_pair(i, j);
                nEdge.dest = make_pair(nX, nY);
                nEdge.weight = costMapGrid[nX][nY];
                edges.emplace_back(nEdge);

                edgeCount++;
            }
        }
    }

    bool breakAway;
    for(int v = 0; v < vertexCount-1; ++v){
        breakAway = true;
        for (int w = 0; w < edgeCount; ++w){

//              int src, int dest, int weight;
            EDGE curEdg = edges[w];
            pair<int, int> src = curEdg.src;
            pair<int, int> dest = curEdg.dest;
            int weight = curEdg.weight;

            string srcStrKey = pts(src.first, src.second);
            string destStrKey = pts(dest.first, dest.second);

            bool isInfinity = true;
            if (value.find(srcStrKey) != value.end()) isInfinity = false;

            bool underWeight = false;
            if (!isInfinity &&
                (value.find(srcStrKey)->second + weight) < value.find(destStrKey)->second)
                underWeight = true;

            if(!isInfinity && underWeight){
//            if (value[src] != INT_MAX && value[src] + weight < value[dest]){

//                v = dest, u = src weight
//                value[v] = value[u] + weight;
                value[destStrKey] = value[srcStrKey] + weight;
//                parent[v]  = u;
                parent[destStrKey] = srcStrKey;
//                cost_par[v] = value[v];
                parentCost[destStrKey] = value[destStrKey];

//                updated = true;
                breakAway = false;
            }
        }

        if (breakAway) break;
    }

    //check for negative edge cycles
    for (int y = 0; y < edgeCount && !breakAway; ++y){
        EDGE yEdge = edges[y];

        //    int uu = Edges[ii].src;
        pair<int,int> ySrc = yEdge.src;

        //    int vv = edges[ii].dest;
        pair <int, int> yDest = yEdge.dest;

        //    int ww = edges[ii].weight;
        int yWeight = yEdge.weight;

        string u = pts(yEdge.src.first, yEdge.src.second);
        string v = pts(yEdge.dest.first, yEdge.dest.second);

        bool isInfinity = false;
        if (value.find(u) == value.end()) isInfinity = true;

    //    if(value[uu] != INT_MAX && value[uu] + ww < value[vv]) {
        if(!isInfinity && value[v] + yWeight < value[v]) {
            cout << "Graph has a negative edge cycle\n";
            return;
        }
    }


    //print shortest path
    //for (int ii = 0; ii < vertexCount; ++ii) {
    for (auto p: parent){
        string pkey = p.first;
        string pval = p.second;
        //    cout << "u->v: " << parent[ii] << "--" << ii << " Cost to reach ";
        cout << "u->v: " << pval << "--" << pkey << " Cost to reach ";
        //    cout << parent[ii] << " from source equals " << value[ii] << "\n";
        cout << pval << " from source equals " << value[pkey] << "\n";
    }


}


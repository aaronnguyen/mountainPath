//
// Created by aaronnguyen on 12/3/20.
//

#include "shortestPath.h"
#include <bits/stdc++.h> // for INT_MAX


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

    // Need to initialize parent and value;
    string firstkey = pts(start.first, start.second);
    parent[firstkey] = pts(0,0); // parent is itself.
    value[firstkey] = 0;

    vector<EDGE> edges;

    auto print_um_str = [](unordered_map<string, string> um, string name){
        cout << name << "\n=======\n";
        for(auto u: um){
            cout << u.first << " " << u.second << "\n";
        }
        cout << "====\n";
    };
    auto print_um_int = [](unordered_map<string, int> um, string name){
        cout << name << "\n=======\n";
        for(auto u: um){
            cout << u.first << " " << to_string(u.second) << "\n";
        }
        cout << "====\n";
    };
    auto print_edges = [pts](vector<EDGE> edges){
        cout << "EDGES\n=======\n";
        for (auto e: edges){
            cout << "Source: (" << pts(e.src.first, e.src.second) << ")\n";
            cout << "Destin: (" << pts(e.dest.first, e.dest.second) << ")\n";
            cout << "Weight: " << to_string(e.weight) << "\n";
        }
    };


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
                value[pts(nX,nY)] = INT_MAX;
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

            if(value.find(srcStrKey)->second != INT_MAX &&
               (value.find(srcStrKey)->second + weight) < value.find(destStrKey)->second){
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

            print_um_int(value, "Value");
            print_um_str(parent, "Parent");
            print_um_int(parentCost, "ParentCost");
            cout << "BREAK\n";
        }

        if (breakAway) {
            cout << "breaking away\n";
            break;
        }
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

    cout << pts(end.first, end.second) << "\n";
    cout << value[pts(end.first, end.second)];

}


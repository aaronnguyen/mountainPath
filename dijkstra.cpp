//
// Created by aaronnguyen on 12/8/20.
//


#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include "dijkstra.h"
#include <bits/stdc++.h> // for INT_MAX
#include <sstream>
using namespace std;


void printShortRoute(shortRoute solution) {

    cout << solution.routeCost << "\n";

    for (auto s: solution.routeGuidance){
        cout << s.first << " " << s.second << "\n";
    }
}


shortRoute dijkstra::shortPath(
        vector<vector<int>> &costMapGrid, pair<int, int> &start, pair<int, int> &end) {

    int maxRow = costMapGrid.size();
    int maxCol = costMapGrid[0].size();
    int numCells = maxRow*maxCol;
    int endIdx;

    vector<int> fromIndex(numCells, -1);
    vector<bool> deadEnd(numCells, false);
    vector<int> dCost(numCells, INT_MAX);
    dCost[0] = 0; // initialize the starting point.

    vector<vector<int>> moveDir = {{0,1}, {1,0}, {0,-1}, {-1, 0}};
    auto inBounds = [maxRow, maxCol](int x, int y){
        return x >= 0 && y >= 0 && x < maxRow && y < maxCol;
    };

    unordered_map<string, int> coordToIndexMap;
    unordered_map<int, string> indexToCoordMap;
    auto coordToString = [](int x, int y) -> string {
        return to_string(x) + " " + to_string(y);
    };

    auto getCoord = [](unordered_map<int, string> &indexToCoordMap, int idx) -> string {
        auto im = indexToCoordMap.find(idx);
        if (im == indexToCoordMap.end()) return "";
        else return im->second;
    };

    // initialize the start of the iteration
    int currX = start.first, currY = start.second;
    int nextIdx = 0;

    int currIdx = 0;
    string coordKey = coordToString(currX, currY);
    coordToIndexMap[coordKey] = currIdx;
    indexToCoordMap[currIdx] = coordKey;
    dCost[currIdx] = 0;
    string endKey = coordToString(end.first, end.second);


    typedef pair<int, int> pairInt;

        // Find the lowest index based on cost value. return first instance.
    // TODO: convert this portion to priority queue searching
    auto getNextIndex = [](vector<bool> &deadEnd, vector<int> &dCost) -> int {

//        for (int i = 0; i < deadEnd.size(); ++i){
//            bool b = deadEnd[i];
//            cout << i << ":";
//            if (b) cout << "T";
//            else cout << "F";
//            cout << ", ";
//        }
//        cout << endl;
//
//        for (int i = 0; i < dCost.size(); ++i){
//
//            string outstring = "I";
//            if (dCost[i]  != INT_MAX) outstring = to_string(dCost[i]);
//            cout << i << ":" << outstring << ", ";
//        }
//        cout << endl;

        priority_queue<pairInt, vector<pairInt>, greater<pairInt> > pq;
        for (int i = 0; i < dCost.size(); ++i){
            if (dCost[i] < INT_MAX && !deadEnd[i]){
                pq.push(make_pair(dCost[i], i));
                // push in dCost first, then the index. then min heap based on dCost value.
            }
        }
//        string wait; cin >> wait;

        return pq.top().second;
    };



    // Iterate through the costMapGrid
    while (coordKey != endKey){

        deadEnd[currIdx] = true;
        int currCost = dCost[currIdx] + costMapGrid[currX][currY];

        for (auto m: moveDir){
            int newX = currX+m[0], newY = currY+m[1];
            if (inBounds(newX, newY)){
                string newCoordKey = coordToString(newX, newY);
                int newIdx = getIndex(coordToIndexMap, newCoordKey);
                if (newIdx < 0) {
                    nextIdx++;
                    newIdx = nextIdx;
                    coordToIndexMap[newCoordKey] = newIdx;
                    indexToCoordMap[newIdx] = newCoordKey;
                }

                if (currCost < dCost[newIdx]){
                    dCost[newIdx] = currCost;
                    fromIndex[newIdx] = currIdx;
                }
            }
        }

        // get the next index (lowest value) and place it into currIdx
        currIdx = getNextIndex(deadEnd, dCost);

        // set coordKey to the next index.
        coordKey = getCoord(indexToCoordMap, currIdx);

        pair<int,int> nextCoordXY = stringToPair(coordKey);
        currX = nextCoordXY.first;
        currY = nextCoordXY.second;

        if (coordKey == endKey){
            endIdx = currIdx;
            deadEnd[endIdx] = true;
        }
    }


    // Build the final solution and return
    auto coordToPair = [](string inString) -> pair<int,int> {
        stringstream strStream(inString);
        int num1, num2;
        strStream >> num1;
        strStream >> num2;
        return make_pair(num1, num2);
    };

    vector<pair<int,int>> route;
    int idxFollow = endIdx;

    while(idxFollow != -1){
        pair<int, int> pCoord = coordToPair(getCoord(indexToCoordMap, idxFollow));
        route.emplace_back(pCoord);
        idxFollow = fromIndex[idxFollow];
    }
    reverse(route.begin(), route.end());

    shortRoute sr;
    sr.routeCost = dCost[endIdx];
    sr.routeGuidance = route;
    return sr;
}

int dijkstra::getIndex(unordered_map<string, int> &coordToIndexMap, string &s) {
    auto cm = coordToIndexMap.find(s);
    if (cm == coordToIndexMap.end()) return -1;
    else return cm->second;
}

pair<int, int> dijkstra::stringToPair(string s) {

    stringstream ss(s);
    pair<int, int> r;
    ss >> r.first;
    ss >> r.second;
    return r;
}

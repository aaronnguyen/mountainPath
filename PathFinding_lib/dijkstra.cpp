//
// Created by aaronnguyen on 12/8/20.
//

#include "dijkstra.h"

using namespace std;

pair<int, string> dijkstra::calculatePath(vector<vector<int>> &costMapGrid, pair<int, int> &start, pair<int, int> &end) {

    // need to make sure costMapGrid is square
    set<int> rowLengths;
    for (auto row: costMapGrid){
        rowLengths.insert(row.size());
    }
    if (rowLengths.size() > 1) return make_pair(-2, "costMapGrid not rectangle.");

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

    // check if start and end are in bounds.
    if (!inBounds(start.first, start.second)) return make_pair(-4, "Start Out of Bounds.");
    if (!inBounds(end.first, end.second)) return make_pair(-4, "End Out of Bounds.");

    unordered_map<string, int> coordToIndexMap;
    unordered_map<int, string> indexToCoordMap;

    auto stringToPair = [](string s) -> pair<int,int> {
        stringstream ss(s);
        pair<int, int> r;
        ss >> r.first;
        ss >> r.second;
        return r;
    };

    auto getIndex = [](unordered_map<string, int> &coordToIndexMap, string &s) -> int {
        auto cm = coordToIndexMap.find(s);
        if (cm == coordToIndexMap.end()) return -1;
        else return cm->second;
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
    priority_queue<pairInt, vector<pairInt>, greater<pairInt> > pq;

    // Iterate through the costMapGrid
    while (coordKey != endKey){

        deadEnd[currIdx] = true;
        int gridCost = costMapGrid[currX][currY];
        if (gridCost < 0) return make_pair(-3, "Negative Weight found.");
        int newCost = dCost[currIdx] + gridCost;

        for (auto m: moveDir){
            int newX = currX+m[0], newY = currY+m[1];
            if (inBounds(newX, newY)){
                string newCoordKey = coordToString(newX, newY);
                int newIdx = getIndex(coordToIndexMap, newCoordKey);

                // if index not found, then create a new reference for it.
                if (newIdx < 0) {
                    nextIdx++;
                    newIdx = nextIdx;
                    coordToIndexMap[newCoordKey] = newIdx;
                    indexToCoordMap[newIdx] = newCoordKey;
                }

                if (newCost < dCost[newIdx]){
                    dCost[newIdx] = newCost;
                    fromIndex[newIdx] = currIdx;
                    pq.push(make_pair(newCost, newIdx));
                }
            }
        }

        // get the next index (lowest value) and place it into currIdx
        pair<int,int> currNode = pq.top();
        pq.pop();
        currIdx = currNode.second;

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

    routeCost = dCost[endIdx];
    routeGuidance = route;

    return make_pair(0, "Success");
}

string dijkstra::coordToString(int x, int y) {
    return to_string(x) + " " + to_string(y);
}

string dijkstra::getCoord(unordered_map<int, string> &indexToCoordMap, int idx) {
    auto im = indexToCoordMap.find(idx);
    if (im == indexToCoordMap.end()) return "";
    else return im->second;
}



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
using namespace std;


void printShortRoute(shortRoute solution) {

    cout << solution.routeCost << "\n";

    for (auto s: solution.routeGuidance){
        cout << s.first << " " << s.second << "\n";
    }
}


shortRoute dijkstra::shortPath(vector<vector<int>> &costMapGrid, pair<int, int> &start, pair<int, int> &end) {

    int maxRow = costMapGrid.size();
    int maxCol = costMapGrid[0].size();
    int nodeAmount = maxRow*maxCol;

    vector<dNode> weightRow(nodeAmount, dNode());
    for (int i = 0; i < weightRow.size(); ++i){
        weightRow[i].weight = INT_MAX;
        weightRow[i].index = i;
    }
    vector<bool> completed(nodeAmount, false);
    unordered_map<string, int> coorToIndex;
    auto coorToString = [](int x, int y) -> string {
        return to_string(x) + "," + to_string(y);
    };

    auto inBounds = [maxRow, maxCol](int x, int y) -> bool {
        return x >= 0 && x < maxRow && y >=0 && y < maxCol;
    };

    vector<vector<int>> moveDir = {{0,1},{0,-1},{1,0},{-1,0}};

    int maxIndex = 0;
    int completedNodes = 0;


    weightRow[0].weight = 0;
    weightRow[0].fromNode = -1;
    weightRow[0].coordinate = start;
    completedNodes++;
//
//    typedef pair<int, dNode> dPair;
//    priority_queue<dPair, vector<dPair>, greater<dPair>> dNodeLow;

    typedef pair<int, int> pairInt;
    priority_queue<pairInt, vector<pairInt>, greater<pairInt>> dNodeLow;

    dNodeLow.push(make_pair(0, 0));

    while(!dNodeLow.empty()){

//        cout << "weightRow: ";
        for (auto wr: weightRow){
            string w_weight;
            if (wr.weight != INT_MAX) w_weight = to_string(wr.weight);
            else w_weight = "I";
            cout << wr.index << "-" << w_weight << "-" << wr.fromNode << ",";
        }
        cout << "\n";

        pair<int,int> pqTop = dNodeLow.top();
        dNodeLow.pop();
        int currentWeight = pqTop.first;
        int currentIndex = pqTop.second;


        if (completed[currentIndex]){
            continue;
        }
        else {
            completedNodes++;
            completed[currentIndex] = true;
        }

//        cout << currentIndex << "\n";


        for (auto dir: moveDir){
            int oldX = weightRow[currentIndex].coordinate.first;
            int oldY = weightRow[currentIndex].coordinate.second;
            int newX = oldX + dir[0];
            int newY = oldY + dir[1];
            if (!inBounds(newX, newY)) continue;

            // check if the node has been traveled to yet.
            string idxKey = coorToString(newX, newY);
            auto keyFound = coorToIndex.find(idxKey);
            int nextIndex;
            if (keyFound == coorToIndex.end()){
                maxIndex++;
                nextIndex = maxIndex;
                coorToIndex.insert({idxKey, nextIndex});
            }
            else
                nextIndex = keyFound->second;



            int newWeight = weightRow[currentIndex].weight + costMapGrid[oldX][oldY];
            if (newWeight < weightRow[nextIndex].weight){
                weightRow[nextIndex].weight = newWeight;
                weightRow[nextIndex].index = nextIndex;
                weightRow[nextIndex].fromNode = currentIndex;
                weightRow[nextIndex].coordinate = make_pair(newX, newY);

//                cout << newWeight << "::" << nextIndex << "\n";
                dNodeLow.push(make_pair(newWeight, nextIndex));
            }
        }
    }


//
//    buildShortRoute
    cout << "Route:\n";
    vector<int> idxPath;


    auto endIdxFind = coorToIndex.find(coorToString(end.first, end.second));
    int endIdx;

    if (endIdxFind != coorToIndex.end()) endIdx = endIdxFind->second;
    else return shortRoute();
    endIdx--;
//    cout << endIdx << "\n\n";
    idxPath.emplace_back(endIdx);

    int nextIdx = endIdx;
    int i = 16;
    do{
        i--;
        int fromN = weightRow[nextIdx].fromNode;
        idxPath.emplace_back(fromN);

        nextIdx = fromN;
    }while  (nextIdx  != 0 );

    shortRoute sr;
    sr.routeCost = weightRow[endIdx].weight;
    for (int x = idxPath.size()-1; x >= 0; --x){
        sr.routeGuidance.emplace_back(weightRow[x].coordinate);
    }


    for (auto s: weightRow){
        cout << s.index << ":: (" << s.coordinate.first << " , " << s.coordinate.second << ");\n";
    }


    return sr;
}
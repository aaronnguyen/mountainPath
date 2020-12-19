//
// Created by aaronnguyen on 12/13/20.
//

#include "gtest/gtest.h"
#include "dijkstra.h"

TEST(ShortestPathTestSuite, GridNotRectangleTest){

    // We only grab the first row and count the columns,
    // so we will either be out of bounds if we hit a row shorter than the first,
    // or we will ignore any cells that are in rows longer than the first.
    vector<vector<int>> notRect = {{0,0,0}, {0,1,1,1}, {0,2,2,2,2}};
    dijkstra sp;
    pair<int,int> placeHolder = make_pair(0,0);
    pair<int, string> resp = sp.calculatePath(notRect, placeHolder, placeHolder);

    EXPECT_EQ(resp.first, -2);

}


TEST(ShortestPathTestSuite, GridRectangleTest){

    vector<vector<int>> cGrid = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}};
    dijkstra sp;
    pair<int,int> placeHolder = {0,0};
    pair<int, string> resp = sp.calculatePath(cGrid, placeHolder, placeHolder);

    EXPECT_EQ(resp.first, 0);

}



TEST(ShortestPathTestSuite, NegativeWeightTest){

    // Any negative values in grid will cause unnecessary loop (inf?)
    vector<vector<int>> cGrid = {{1,1,1}, {1,1,1}, {1,-2,1}, {1,1,1}};
    dijkstra sp;
    pair<int,int> start = {0,0};
    pair<int,int> end = {2,2};
    pair<int, string> resp = sp.calculatePath(cGrid, start, end);

    EXPECT_EQ(resp.first, -3);

}


TEST(ShortestPathTestSuite, startOutOfBoundsTest){

    // Any negative values in grid will cause unnecessary loop (inf?)
    vector<vector<int>> cGrid = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}};
    dijkstra sp;
    pair<int,int> start = {-1,0};
    pair<int,int> end = {2,2};
    pair<int, string> resp = sp.calculatePath(cGrid, start, end);

    EXPECT_EQ(resp.first, -4);

}


TEST(ShortestPathTestSuite, endOutOfBoundsTest){

    // Any negative values in grid will cause unnecessary loop (inf?)
    vector<vector<int>> cGrid = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}};
    dijkstra sp;
    pair<int,int> start = {0,0};
    pair<int,int> end = {4,2};
    pair<int, string> resp = sp.calculatePath(cGrid, start, end);

    EXPECT_EQ(resp.first, -4);

}

TEST(ShortestPathTestSuite, nullStartEndDefaultsToZerosTest) {
    dijkstra sp;
    vector<vector<int>> cGrid = {{1,1,1}, {1,1,1}};
    pair<int, int> nullCoord;
    pair<int, int> notNull = {1,1};

    pair<int, string> resp = sp.calculatePath(cGrid, nullCoord, notNull);
    vector<pair<int,int>> r = sp.getRoute();
    pair<int, int> startPoint = r[0];

    pair<int, string> resp2 = sp.calculatePath(cGrid, notNull, nullCoord);
    vector<pair<int,int>> r2 = sp.getRoute();
    pair<int,int> endPoint = r2[r2.size()-1];

    pair<int, int> expected = {0,0};
    EXPECT_EQ(expected, startPoint);
    EXPECT_EQ(expected, endPoint);

}

TEST(ShortestPathTestSuite, costNoPathTest) {
    dijkstra sp;
    EXPECT_EQ(-1, sp.getCost());
    // Cost should be > 0, so returning -1 is an invalid answer.
}

TEST(ShortestPathTestSuite, routeNoPathTest) {
    dijkstra sp;
    vector<pair<int,int>> noData;
    EXPECT_EQ(noData, sp.getRoute());

}
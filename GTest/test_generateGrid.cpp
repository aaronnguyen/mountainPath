//
// Created by aaronnguyen on 12/13/20.
//

#include "gtest/gtest.h"
#include "generate_grid.h"

TEST(GenerateGridTestSuite, GridGenTest){
    // only takes in one int val, will always generate a square grid.
    int expectedVal = 23; // randomly selected number of no importance.
    generate_grid gg;
    costGrid cg = gg.generateRandomGrid(expectedVal);

    EXPECT_EQ(cg.rowCount, expectedVal);
    EXPECT_EQ(cg.colCount, expectedVal);

    EXPECT_EQ(expectedVal, cg.grid.size());
    for(auto row: cg.grid){
        EXPECT_EQ(expectedVal, row.size());
    }
}

TEST(GenerateGridTestSuite, GridGenAlwaysPositiveTest){

    generate_grid gg;
    bool nonPositiveFound = false;

    // Generate multiple grids of various sizes, 5x5, 6x6, ... 10x10
    // then check each variable inside.
    for(int i = 5; i <= 10; ++i){
        costGrid cg = gg.generateRandomGrid(i);
        for(auto row: cg.grid){
            for (auto col: row){
                // range is actually 10-99. trying to keep them all 2 digits
                // to get as much diversity, while also keeping some form
                //      of conformity, so when we cout, everything lines up.
                if (col < 1) nonPositiveFound = true;
            }
        }
    }

    EXPECT_EQ(nonPositiveFound, false);
}


TEST(GenerateGridTestSuite, negativeNumberGenTest) {

    generate_grid gg;
    int negativeInt = -5;
    costGrid cg = gg.generateRandomGrid(negativeInt);
    // basic for logic loop. for (int i = 0; i < amt ...
    // so it should be an empty grid.

    vector<vector<int>> empty;
    EXPECT_EQ(cg.grid, empty);

    // Regardless of what the input is for the generate random.
    // should calculate the row and col count independently.
    EXPECT_EQ(cg.rowCount, 0);
    EXPECT_EQ(cg.colCount, 0);

}


TEST(GenerateGridTestSuite, costGridStartEndGenTest) {

    generate_grid gg;

    int negativeInt = -5;
    costGrid cg = gg.generateRandomGrid(negativeInt);
    // basic for logic loop. for (int i = 0; i < amt ...
    // so it should be an empty grid.

    vector<vector<int>> empty;
    EXPECT_EQ(cg.grid, empty);

    // Regardless of what the input is for the generate random.
    // should calculate the row and col count independently.
    EXPECT_EQ(cg.rowCount, 0);
    EXPECT_EQ(cg.colCount, 0);

}


TEST(GenerateGridTestSuite, defaultLastCellEndTest) {

    generate_grid gg;
    costGrid cg;
    int lastIndex;
    pair<int,int> lastCell;

    for (int i = 5; i <= 10; ++i){
        cg = gg.generateRandomGrid(i);

        lastIndex = i-1; // because 0 based.
        lastCell = {lastIndex, lastIndex};
        EXPECT_EQ(lastCell, cg.end);

    }

    // although invalid, just to check math
    int i = -5;
    lastCell = {i-1, i-1};
    cg = gg.generateRandomGrid(i);
    EXPECT_EQ(lastCell, cg.end);


}



TEST(GenerateGridTestSuite, defaultFirstCellTest) {

    generate_grid gg;
    costGrid cg;
    pair<int,int> firstCell = {0, 0};

    for (int i = -5; i <= 10; ++i){
        cg = gg.generateRandomGrid(i);

        EXPECT_EQ(firstCell, cg.start);
    }

}
//
// Created by aaronnguyen on 12/13/20.
//

#include "gtest/gtest.h"
#include "generate_grid.h"

TEST(GenerateGridTestSuite, GridGenTest){

    generate_grid gg(-1);
    costGrid cg = gg.generateRandomGrid(10);

    EXPECT_EQ(cg.rowCount, 10);
    EXPECT_EQ(cg.colCount, 10);


}
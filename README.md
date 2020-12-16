# mountainPath
Shortest Path Problem

## Build Notes
```bash
# from within project root directory
mkdir cmake_build
cd cmake_build
cmake ..
make
```

Will build and link the main program and the google tests as well.

## Run Notes

USAGE: `./mountainPath ${INT_I}` 

Where INT_I will create the grid of size INT_I x INT_I and the end point will be (INT_I,INT_I)


```bash

# e.g.:
./PathFinding_run 10


# To run google tests
./GTest/Google_Tests_run
```

## Time Binary Notes

Using time binary to get the Time in seconds and Memory in KBytes.

```bash
\time --format="\n\nTime Report\nMemory: %M kb\nTime: %e secs" ./PathFinding_run 10
```

Time reports time in seconds, but smaller grids will not be measurable, so the program itself will also calculate ms.
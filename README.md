# mountainPath
Shortest Path Problem


## Run Notes:
```bash
# USAGE: ./mountainPath ${INT_I}
#           where INT_I will create the grid of size INT_I x INT_I
#           and where the end point will be (INT_I,INT_I)

# e.g.:
./mountainPath 10
```

## Time Binary Notes:

Using time binary to get the Time in seconds and Memory in KBytes.

```bash
\time --format="\n\nTime Report\nMemory: %M kb\nTime: %e secs" ./mountainPath 10
```

Note: Time reports time in seconds, but smaller grids will not be measurable, so the program itself will calculate ms of the search algorithm.
### compile：
```bash
g++ -std=c++17 -O3 -o hw2 hw2.cpp
```

### output
```bash
--- Performance Report ---
Total Market Ticks Processed: 100000
Total Orders Placed: 94011
Average Tick-to-Trade Latency (ns): 45692803
Maximum Tick-to-Trade Latency (ns): 69664667
Signal 1 Count: 10001
Signal 2 Count: 93207
Signal 3 Count: 16807
--------------------------
Total Runtime (ms): 85
```

### comment:
1. I add some count function to record the time that a signal triggered. Signal 1 Count: 10001, Signal 2 Count: 93207,Signal 3 Count: 16807
2. There are still many ways to optimize
   1. use multi-processing to speed up the process like one process for each signal
   2. rewrite the vector STL
   3. calc Avg use too much time and it is O(n), we can use a new indicate variable to record the sum of all signals and the count of all signals, then we can calc the average in O(1)
3. if we have more than 10x data, the code will be more efficient. tie total running time is 85ms, if we have 1M data, the total running time will be 651ms. However when we use O3 optimization, the total running time will be 91ms. 
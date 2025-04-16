# HW3

## Task 1
### get started

```bash
make
./task1
```

### Answers

1. We need to use `delete[]` to delete the array of trades. delete [] will free the memory allocated for the array of trades.
2. if you forget to use delete [] to free the memory allocated for the array of trades, you will have memory leak. 
But in the end, the program will still run and call the destructor.
3. you can not double delete the same memory it will have a error like this:
```bash
Symbol: AAPL
Price: 150.75

Array of trades:
Symbol: AAPL, Price: 150.75
Symbol: GOOG, Price: 2800.12
Symbol: MSFT, Price: 210.22
Symbol: AMZN, Price: 3300.77
Symbol: TSLA, Price: 720.46
task1(86684,0x1ecba8840) malloc: Double free of object 0x133104100
task1(86684,0x1ecba8840) malloc: *** set a breakpoint in malloc_error_break to debug
zsh: abort      ./task1
```

## Task 2
debug and comment
```cpp  
#include <iostream>
#include <string>

struct Trade {
    std::string symbol;
    double price;

    Trade(const std::string& s, double p) : symbol(s), price(p) {
        std::cout << "Trade created: " << symbol << "\n";
    }

    ~Trade() {
        std::cout << "Trade destroyed: " << symbol << "\n";
    }
};

int main() {
    Trade* t1 = new Trade("AAPL", 150.0);
    Trade* t2 = new Trade("GOOG", 2800.0);
    delete t1;
    // delete t1; // this is a double delete, which will cause undefined behavior.

    Trade* t3 = new Trade("MSFT", 300.0);
    t3 = new Trade("TSLA", 750.0); // This creates a memory leak because the memory allocated for "MSFT" is lost. when t3 is reassigned without first being deleted. The "MSFT" Trade object is still in memory but can no longer be accessed or freed.

    Trade* trades = new Trade[3] {
        {"NVDA", 900.0},
        {"AMZN", 3200.0},
        {"META", 250.0}
    };
    delete trades; // trades is a pointer thus we should use delete [] to 

    return 0;
}
```

## Task 3
The source code is in task3.cpp. 
Here is how to use the code:
``` bash
make
./task3
```

## Task 4
the source code is also in task3.cpp.
Here is how to use the code:
``` bash
make
./task3
```
And in this task, I use the same code template in task3.cpp.
And I also modify the code to make it more efficient. And add some features to allow shared ownership.

## Task 5

### Answers

1. Here are three problems that may happen when you manually manage memory:
    - Memory leak: You may forget to free the memory, which will cause memory leak.
    - Dangling pointer: You may delete the memory, but the pointer is still pointing to the memory, which will cause undefined behavior.
    - Double free: You may free the memory twice, which will cause undefined behavior.
2. When memory leakage happends in HFT system. it will cause the program shut down and then it will have some unknown behavior like crash and more exposure to some risk.
3. RAII is a programming concept that ensures that resources are properly released when they are no longer needed.By using RAII, we can ensure that the memory is properly released when the program shuts down.This can reduce the risk of bugs like memory leak and dangling pointer.
4. It you use automatic memory management, you don't need to worry about memory leak and dangling pointer. However, a lot of checks are needed to ensure the memory is properly released which will cost more time and resources. Thus makes the program slower and have 
less chance to catch the trade opportunity.



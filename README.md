# finm327
Finmath 32700 source code repo
Team Members: Benchen Liu, Zhengyun Xu

## develop calendar
0329 init this repo and write baseline function. Need to write makefile. 

### Get started
We use makefile to compile the source code.

Makefile code and comment are will written.

All you have to do is to type `make` in the terminal.
```bash
make
./bin/program
```

If you want to open debug mode, you can type `make debug` in the terminal.
```bash
make debug
./bin/program
```



## matrix computation kernal
In this module we try to implement four functions regarding matrix multiplication.

1. Explain the key differences between pointers and references in C++. 
   When would you choose to use a pointer over a reference, and vice versa, in the context of implementing numerical algorithms?
   
   Pointers can be null and reassigned; references must be bound at initialization and cannot be null. 
   In numerical algorithms, use pointers for optional or dynamically allocated data, and references for guaranteed inputs or outputs without ownership transfer.

2. How does the row-major and column-major storage order of matrices affect memory access patterns and cache locality during matrix-vector and matrix-matrix multiplication? 
   Provide specific examples from your implementations and benchmarking results.

   Row-major storage allows sequential memory access when traversing rows, improving cache locality. 
   In matrix-vector multiplication, the row-major version was faster due to contiguous access, while the column-major version showed poorer performance due to strided access. 
   In matrix-matrix multiplication, transposing matrix B enabled row-wise access, reducing cache misses and improving performance over the naive version.

3. Describe how CPU caches work (L1, L2, L3) and explain the concepts of temporal and spatial locality.
   How did you try to exploit these concepts in your optimizations?

   CPU caches (L1, L2, L3) are fast memory layers closer to the CPU, with L1 being the smallest and fastest.
   Temporal locality means reusing the same data soon; spatial locality means accessing nearby data.
   We exploited these by reordering loops and using blocking to access memory in a sequential and reusable pattern.

4. What is memory alignment, and why is it important for performance?
   Did you observe a significant performance difference between aligned and unaligned memory in your experiments? Explain your findings.

   Memory alignment means placing data at memory addresses that are multiples of a specific boundary (e.g., 64 bytes).
   It helps the CPU load data more efficiently and enables vectorized instructions. 
   In our experiments, alignment showed minimal performance difference, likely because the data sizes and access patterns did not heavily stress alignment-sensitive operations.

5. Discuss the role of compiler optimizations (like inlining) in achieving high performance. 
   How did the optimization level affect the performance of your baseline and optimized implementations? 
   What are the potential drawbacks of aggressive optimization?

   Compiler optimizations like inlining reduce function call overhead and improve instruction scheduling. 
   Higher optimization levels (e.g., -O3) significantly improved performance across all implementations. 
   However, aggressive optimization can increase binary size, reduce debuggability, and sometimes lead to unexpected behavior due to reordered instructions.

6. Based on your profiling experience, what were the main performance bottlenecks in your initial implementations? 
   How did your profiling results guide your optimization efforts?

   需要填入！！！

7. Reflect on the teamwork aspect of this assignment.
   How did dividing the initial implementation tasks and then collaborating on analysis and optimization work?
   What were the challenges and benefits of this approach?

   Dividing initial implementation tasks allowed parallel progress and saved time. 
   Collaborating on analysis and optimization helped combine different insights and catch performance issues more effectively.
   The main challenge was ensuring consistent coding styles and merging ideas, but the shared understanding built during optimization was a major benefit.
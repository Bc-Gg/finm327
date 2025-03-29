/*
Use three kind of methods to speed up the matrix summation.
1. use inline function: just add in the loop rather than call the function.
2. use pointer to access the matrix element
3. iterate row by row to take advantage of row-major order
4. use -o3 optimization

Best compile command:
g++ -std=c++2a -O3 -march=native  hw1matrix.cpp -o hw1matrix

Without O3 optimization:
Basic Sum: 401049
Basic Time: 51 milliseconds
Optimized Sum: 401049
Optimized Time: 8 milliseconds

With O3 optimization:
Basic Sum: 162209
Basic Time: 1 milliseconds
Optimized Sum: 162209
Optimized Time: 1 milliseconds

*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

const int SIZE = 4096;

// Basic function to access matrix elements
int getElement(const std::vector<std::vector<int>> &matrix, int row, int col)
{
    return matrix[row][col];
}

// Basic function to add two integers
int add(int a, int b)
{
    return a + b;
}

inline int getElementPointer(const std::vector<std::vector<int>> &matrix, int row, int col)
{
    const std::vector<int> *rowPointer = matrix.data() + row;
    const int *elementPointer = rowPointer->data() + col;
    return *elementPointer;
}

// inline function to add two integers
inline int addInline(int a, int b)
{
    return a + b;
}

// Optimized summation function
long long sumMatrixOptimized(const std::vector<std::vector<int>> &matrix)
{
    long long sum = 0;

    // Iterate row by row to take advantage of row-major order
    for (int i = 0; i < SIZE; ++i)
    {
        const int *row = matrix[i].data(); // Access the row as a pointer
        for (int j = 0; j < SIZE; ++j)
        {
            sum += row[j]; // Use pointer access for better cache utilization
        }
    }
    return sum;
}

// Unoptimized summation function
long long sumMatrixBasic(const std::vector<std::vector<int>> &matrix)
{
    long long sum = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            sum = add(sum, getElement(matrix, i, j));
        }
    }
    return sum;
}

int main()
{
    // Generate a large random matrix
    std::vector<std::vector<int>> matrix(SIZE, std::vector<int>(SIZE));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-100, 100);
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            matrix[i][j] = distrib(gen);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    long long sum = sumMatrixBasic(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Basic Sum: " << sum << std::endl;
    std::cout << "Basic Time: " << duration.count() << " milliseconds" << std::endl;

    // Students will implement their optimized version here
    auto start_optimized = std::chrono::high_resolution_clock::now();
    long long optimized_sum = sumMatrixOptimized(matrix);
    auto end_optimized = std::chrono::high_resolution_clock::now();
    auto duration_optimized = std::chrono::duration_cast<std::chrono::milliseconds>(end_optimized - start_optimized);

    std::cout << "Optimized Sum: " << optimized_sum << std::endl;
    std::cout << "Optimized Time: " << duration_optimized.count() << " milliseconds" << std::endl;

    return 0;
}
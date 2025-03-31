#include "matrix_kernal.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

const int SIZE = 500;

int main()
{
    // Generate a large random matrix
    double matrix[SIZE * SIZE];

    // 随机数生成器的初始化
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-10, 10);
    // 填充二维数组
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            matrix[i + j * SIZE] = distrib(gen);
        }
    }
    double result_matrix[SIZE * SIZE];
    // Basic multiplication
    auto start = std::chrono::high_resolution_clock::now();
    multiply_mm_naive(matrix, SIZE, SIZE, matrix, SIZE, SIZE, result_matrix);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // std::cout << "Basic Mul: " << mul << std::endl;
    std::cout << "Basic Time: " << duration.count() << " milliseconds" << std::endl;

    // another way
    auto start_optimized = std::chrono::high_resolution_clock::now();
    long long optimized_mul = 0;
    auto end_optimized = std::chrono::high_resolution_clock::now();
    auto duration_optimized = std::chrono::duration_cast<std::chrono::milliseconds>(end_optimized - start_optimized);

    std::cout << "Optimized Mul: " << optimized_mul << std::endl;
    std::cout << "Optimized Time: " << duration_optimized.count() << " milliseconds" << std::endl;

    return 0;
}
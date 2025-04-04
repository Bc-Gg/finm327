#include "matrix_kernal.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>


int main()
{
    // 1. Simple test for each function
    std::cout << "1. Simple test for each function" << std::endl;
    std::cout << std::endl;

    // Test multiply_mv_row_major
    double matrix1[6] = {1, 2, 3, 4, 5, 6};  // 2x3 matrix (row-major)
    double vector1[3] = {1, 1, 1};
    double result1[2];
    multiply_mv_row_major(matrix1, 2, 3, vector1, result1);
    std::cout << "Test multiply_mv_row_major (should be [6, 15]): " << std::endl;
    std::cout << "Result of multiply_mv_row_major:" << std::endl;
    std::cout << result1[0] << " " << result1[1] << std::endl;
    std::cout << std::endl;

    // Test multiply_mv_col_major
    double matrix2[6] = {1, 4, 2, 5, 3, 6};  // 2x3 matrix in column-major order
    double result2[2];
    multiply_mv_col_major(matrix2, 2, 3, vector1, result2);
    std::cout << "Test multiply_mv_row_major (should be [6, 15]): " << std::endl;
    std::cout << "Result of multiply_mv_col_major:" << std::endl;
    std::cout << result2[0] << " " << result2[1] << std::endl;
    std::cout << std::endl;

    // Test multiply_mm_naive
    double matrixA[6] = {1, 2, 3, 4, 5, 6};  // 2x3
    double matrixB[6] = {7, 8, 9, 10, 11, 12};  // 3x2
    double result3[4];
    multiply_mm_naive(matrixA, 2, 3, matrixB, 3, 2, result3);
    std::cout << "Test multiply_mm_naive (should be [58 64; 139 154]):" << std::endl;
    std::cout << "Result of multiply_mm_naive:" << std::endl;
    std::cout << result3[0] << " " << result3[1] << std::endl;
    std::cout << result3[2] << " " << result3[3] << std::endl;
    std::cout << std::endl;

    // Test multiply_mm_transposed_b
    double matrixB_T[6] = {7, 9, 11, 8, 10, 12};  // Transposed B (2x3), stored row-major
    double result4[4];
    multiply_mm_transposed_b(matrixA, 2, 3, matrixB_T, 3, 2, result4);
    std::cout << "Test multiply_mm_naive (should be [58 64; 139 154]):" << std::endl;
    std::cout << "Result of multiply_mm_transposed_b:" << std::endl;
    std::cout << result4[0] << " " << result4[1] << std::endl;
    std::cout << result4[2] << " " << result4[3] << std::endl;
    std::cout << std::endl;


    // 2. Benchmarking
    std::cout << "2. Benchmarking" << std::endl;
    std::cout << std::endl;

    int runs = 50;
    int sizes[3] = {3, 20, 100};
    for (int size: sizes){
        benchmark(size, runs, "vector");
        benchmark(size, runs, "matrix");
    }

    // 3. Cache Locality Analysis
    std::cout << "3. Cache Locality Analysis" << std::endl;
    std::cout << std::endl;

    // 4. Memory Alignment
    std::cout << "4. Memory Alignment" << std::endl;
    std::cout << std::endl;

    for (int size: sizes) {
        std::cout << "===== Unaligned Benchmark =====" << std::endl;
        benchmark(size, runs, "matrix");

        std::cout << "===== Aligned =====" << std::endl;
        benchmark_aligned(size, runs);
    }

    // 5. Inlining
    std::cout << "5. Inlining" << std::endl;
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-10, 10);

    for (int size: sizes) {
        std::vector<double> durations1;
        std::vector<double> durations2;

        for (int r = 0; r < runs; ++r) {
            double matrixA[size * size];
            for (int i = 0; i < size; ++i){
                for (int j = 0; j < size; ++j){
                    matrixA[i * size + j] = distrib(gen);
                }
            }

            double result1[size * size];
            double result2[size * size];

            double vector[size];
            for (int i = 0; i < size; ++i){
                vector[i] = distrib(gen);
            }

            auto start = std::chrono::high_resolution_clock::now();
            multiply_mv_col_major(matrixA, size, size, vector, result1);
            auto end = std::chrono::high_resolution_clock::now();
            double millis = std::chrono::duration<double, std::milli>(end - start).count();
            durations1.push_back(millis);

            start = std::chrono::high_resolution_clock::now();
            multiply_mv_col_major_inlined(matrixA, size, size, vector, result2);
            end = std::chrono::high_resolution_clock::now();
            millis = std::chrono::duration<double, std::milli>(end - start).count();
            durations2.push_back(millis);
        }

        double sum1 = 0;
        double sum2 = 0;
        for (double d1 : durations1) sum1 += d1;
        for (double d2 : durations2) sum2 += d2;
        double avg1 = sum1 / runs;
        double avg2 = sum2 / runs;

        double variance1 = 0;
        double variance2 = 0;
        for (double d1 : durations1) variance1 += (d1 - avg1) * (d1 - avg1);
        for (double d2 : durations2) variance2 += (d2 - avg2) * (d2 - avg2);
        double stddev1 = std::sqrt(variance1 / runs);
        double stddev2 = std::sqrt(variance2 / runs);

        std::cout << "Size: " << size << std::endl;
        std::cout << "Matrix-Vector-Column"
                  << " | Avg Time: " << avg1 << " ms"
                  << " | Std Dev: " << stddev1 << " ms" << std::endl;
        std::cout << "Matrix-Vector-Column_Inlined"
                  << " | Avg Time: " << avg2 << " ms"
                  << " | Std Dev: " << stddev2 << " ms" << std::endl;
        std::cout << std::endl;
    }

    // In Terminal:
    // -O0:
    // make clean
    // make debug
    // ./bin/program_debug

    // -O3:
    // make
    // ./bin/program

    // 6. Profiling
    std::cout << "6. Profiling" << std::endl;
    std::cout << std::endl;

    

}


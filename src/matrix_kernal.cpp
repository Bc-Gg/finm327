#include "matrix_kernal.h"
#include <iostream>
#include <string>
#include <random>

void multiply_mv_row_major(const double *matrix, int rows, int cols, const double *vector, double *result){
    for(int i = 0; i < rows; i++){
        result[i] = 0;
        for(int j = 0; j < cols; j++){
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

void multiply_mv_col_major(const double *matrix, int rows, int cols, const double *vector, double *result) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[j * rows + i] * vector[j];
        }
    }
}

void multiply_mm_naive(const double *matrixA, int rowsA, int colsA, const double *matrixB, int rowsB, int colsB, double *result){
    if (colsA != rowsB)
    {
        std::cerr << "Matrix dimensions are incompatible for multiplication!" << std::endl;
        return;
    }

    for(int i = 0; i < rowsA; i++){
        for(int j = 0; j < colsB; j++){
            result[i * colsB + j] = 0;
            for(int k = 0; k < colsA; k++){
                result[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
}

/*
Assume matrixA and result are in row-major order, and matrixB_transposed is the transpose of matrix B (also in row-major order)
*/

void multiply_mm_transposed_b(const double *matrixA, int rowsA, int colsA,const double *matrixB_transposed, int rowsB, int colsB, double *result){
    if (colsA != rowsB)
    {
        std::cerr << "Matrix dimensions are incompatible for multiplication!" << std::endl;
        return;
    }

    for (int i = 0; i < rowsA; i++){
        for (int j = 0; j < colsB; j++){
            result[i * colsB + j] = 0;
            for (int k = 0; k < colsA; k++){
                result[i * colsB + j] += matrixA[i * colsA + k] * matrixB_transposed[j * colsA + k];
            }
        }
    }
}

void benchmark(const int size, const int runs, const std::string obj) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-10, 10);

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

        if (obj == "vector"){
            double vector[size];
            for (int i = 0; i < size; ++i){
                vector[i] = distrib(gen);
            }

            auto start = std::chrono::high_resolution_clock::now();
            multiply_mv_row_major(matrixA, size, size, vector, result1);
            auto end = std::chrono::high_resolution_clock::now();
            double millis = std::chrono::duration<double, std::milli>(end - start).count();
            durations1.push_back(millis);

            start = std::chrono::high_resolution_clock::now();
            multiply_mv_col_major(matrixA, size, size, vector, result2);
            end = std::chrono::high_resolution_clock::now();
            millis = std::chrono::duration<double, std::milli>(end - start).count();
            durations2.push_back(millis);
        }
        else {
            double matrixB[size * size];
            for (int i = 0; i < size; ++i){
                for (int j = 0; j < size; ++j){
                    matrixB[i * size + j] = distrib(gen);
                }
            }

            // Transpose B into B_T
            double matrixB_T[size * size];
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    matrixB_T[j * size + i] = matrixB[i * size + j];
                }
            }

            auto start = std::chrono::high_resolution_clock::now();
            multiply_mm_naive(matrixA, size, size, matrixB, size, size, result1);
            auto end = std::chrono::high_resolution_clock::now();
            double millis = std::chrono::duration<double, std::milli>(end - start).count();
            durations1.push_back(millis);

            start = std::chrono::high_resolution_clock::now();
            multiply_mm_transposed_b(matrixA, size, size, matrixB_T, size, size, result2);
            end = std::chrono::high_resolution_clock::now();
            millis = std::chrono::duration<double, std::milli>(end - start).count();
            durations2.push_back(millis);
        }
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

    if (obj == "vector"){
        std::cout << "Size: " << size << std::endl;
        std::cout << "Matrix-Vector-Row"
                  << " | Avg Time: " << avg1 << " ms"
                  << " | Std Dev: " << stddev1 << " ms" << std::endl;
        std::cout << "Matrix-Vector-Column"
                  << " | Avg Time: " << avg2 << " ms"
                  << " | Std Dev: " << stddev2 << " ms" << std::endl;
        std::cout << std::endl;
    }
    else{
        std::cout << "Size: " << size << "x" << size << std::endl;
        std::cout << "Matrix-Matrix-Naive"
                  << " | Avg Time: " << avg1 << " ms"
                  << " | Std Dev: " << stddev1 << " ms" << std::endl;
        std::cout << "Matrix-Matrix-Transposed"
                  << " | Avg Time: " << avg2 << " ms"
                  << " | Std Dev: " << stddev2 << " ms" << std::endl;
        std::cout << std::endl;
    }
}

void benchmark_aligned(const int size, const int runs) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-10, 10);

    std::vector<double> durations1;
    std::vector<double> durations2;

    for (int r = 0; r < runs; ++r) {

        double* matrixA;
        posix_memalign(reinterpret_cast<void**>(&matrixA), 64, sizeof(double) * size * size);
        double* matrixB;
        posix_memalign(reinterpret_cast<void**>(&matrixB), 64, sizeof(double) * size * size);
        double* matrixB_T;
        posix_memalign(reinterpret_cast<void**>(&matrixB_T), 64, sizeof(double) * size * size);
        double* result1;
        posix_memalign(reinterpret_cast<void**>(&result1), 64, sizeof(double) * size * size);
        double* result2;
        posix_memalign(reinterpret_cast<void**>(&result2), 64, sizeof(double) * size * size);

        for (int i = 0; i < size * size; ++i) {
            matrixA[i] = distrib(gen);
            matrixB[i] = distrib(gen);
        }

        // Transpose B into B_T
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrixB_T[j * size + i] = matrixB[i * size + j];
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        multiply_mm_naive(matrixA, size, size, matrixB, size, size, result1);
        auto end = std::chrono::high_resolution_clock::now();
        double millis = std::chrono::duration<double, std::milli>(end - start).count();
        durations1.push_back(millis);

        start = std::chrono::high_resolution_clock::now();
        multiply_mm_transposed_b(matrixA, size, size, matrixB_T, size, size, result2);
        end = std::chrono::high_resolution_clock::now();
        millis = std::chrono::duration<double, std::milli>(end - start).count();
        durations2.push_back(millis);

        free(matrixA); free(matrixB); free(matrixB_T); free(result1); free(result2);
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

    std::cout << "Size: " << size << "x" << size << std::endl;
    std::cout << "Matrix-Matrix-Naive"
              << " | Avg Time: " << avg1 << " ms"
              << " | Std Dev: " << stddev1 << " ms" << std::endl;
    std::cout << "Matrix-Matrix-Transposed"
              << " | Avg Time: " << avg2 << " ms"
              << " | Std Dev: " << stddev2 << " ms" << std::endl;
    std::cout << std::endl;
}
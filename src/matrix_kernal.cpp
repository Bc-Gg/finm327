# include"matrix_kernal.h"
# include<iostream>
# include<cmath>

void multiply_mv_row_major(const double *matrix, int rows, int cols, const double *vector, double *result){
    for(int i = 0; i < rows; i++){
        result[i] = 0;
        for(int j = 0; j < cols; j++){
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

void multiply_mv_col_major(const double *matrix, int rows, int cols, const double *vector, double *result){
    for(int i = 0; i < cols; i++){
        result[i] = 0;
        for(int j = 0; j < rows; j++){
            result[i] += matrix[j * cols + i] * vector[j];
        }
    }
}

void multiply_mm_naive(const double *matrixA, int rowsA, int colsA, const double *matrixB, int rowsB, int colsB, double *result){
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
Assume matrixA and result are in row-major order, and matrixB_transposed is the transpose of matrix B (also in row-major order
*/
#include <iostream>

void multiply_mm_transposed_b(const double *matrixA, int rowsA, int colsA,const double *matrixB_transposed, int rowsB, int colsB, double *result)
{
    if (colsA != rowsB)
    {
        std::cerr << "Matrix dimensions are incompatible for multiplication!" << std::endl;
        return;
    }

    for (int i = 0; i < rowsA; ++i)
    {
        for (int j = 0; j < colsB; ++j)
        {
            double sum = 0.0;
            for (int k = 0; k < colsA; ++k)
            {
                double a = matrixA[i * colsA + k];
                double b = matrixB_transposed[j * colsA + k];
                sum += a * b;
            }
            result[i * colsB + j] = sum;
        }
    }
}

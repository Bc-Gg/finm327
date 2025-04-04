# ifndef MATRIX_KERNAL_H
# define MATRIX_KERNAL_H

#include <string>

void multiply_mv_row_major(const double *matrix, int rows, int cols, const double *vector, double *result);

void multiply_mv_col_major(const double *matrix, int rows, int cols, const double *vector, double *result);

void multiply_mm_naive(const double *matrixA, int rowsA, int colsA, const double *matrixB, int rowsB, int colsB, double *result);

void multiply_mm_transposed_b(const double *matrixA, int rowsA, int colsA, const double *matrixB_transposed, int rowsB, int colsB, double *result);

void benchmark(const int size, const int runs, const std::string obj);

void benchmark_aligned(const int size, const int runs);

inline void multiply_mv_col_major_inlined(const double *matrix, int rows, int cols, const double *vector, double *result) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[j * rows + i] * vector[j];
        }
    }
}





# endif // MATRIX_KERNAL_H
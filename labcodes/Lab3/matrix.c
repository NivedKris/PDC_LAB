#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROWS 3
#define COLS 3

void generate_random_matrix(double matrix[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

void parallel_matrix_addition(double result[ROWS][COLS], double matrix1[ROWS][COLS], double matrix2[ROWS][COLS])
{
#pragma omp parallel for
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void parallel_matrix_multiplication(double result[ROWS][COLS], double matrix1[ROWS][COLS], double matrix2[ROWS][COLS])
{
#pragma omp parallel for
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            result[i][j] = 0.0;
            for (int k = 0; k < COLS; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    double matrix1[ROWS][COLS];
    double matrix2[ROWS][COLS];
    double result_addition[ROWS][COLS];
    double result_multiplication[ROWS][COLS];

    generate_random_matrix(matrix1);
    generate_random_matrix(matrix2);

    parallel_matrix_addition(result_addition, matrix1, matrix2);
    parallel_matrix_multiplication(result_multiplication, matrix1, matrix2);
    printf("NIVED KRISHNA\n2021BCS0028\n");
    printf("Matrix 1:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%.2f\t", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix 2:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%.2f\t", matrix2[i][j]);
        }
        printf("\n");
    }

    printf("\nParallel Matrix Addition Result:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%.2f\t", result_addition[i][j]);
        }
        printf("\n");
    }

    printf("\nParallel Matrix Multiplication Result:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%.2f\t", result_multiplication[i][j]);
        }
        printf("\n");
    }

    return 0;
}

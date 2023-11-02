#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void matrix_multiply(int **A, int **B, int **C, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] *
                           B[k][j];
            }
        }
    }
}
int main()
{
    int matrix_sizes[] = {3, 10, 50, 100, 300, 500, 1000};
    int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);

    for (int k = 0; k < num_sizes; k++)
    {
        int N = matrix_sizes[k];
        int **A, **B, **C;
        A = (int **)malloc(N * sizeof(int *));
        B = (int **)malloc(N * sizeof(int *));
        C = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++)
        {
            A[i] = (int *)malloc(N * sizeof(int));
            B[i] = (int *)malloc(N * sizeof(int));
            C[i] = (int *)malloc(N * sizeof(int));
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A[i][j] = i * N + j;
                B[i][j] = j * N + i;
            }
        }
        clock_t start_time = clock();
        matrix_multiply(A, B, C, N);
        clock_t end_time = clock();
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Matrix size (N x N) = %d x %d\n", N, N);
        printf("Execution Time: %f seconds\n", execution_time);
        printf("--------------------- \n");
        for (int i = 0; i < N; i++)
        {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}

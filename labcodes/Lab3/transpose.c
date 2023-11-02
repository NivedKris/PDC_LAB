#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main()
{
    int N;
    printf("NIVED KRISHNA 2021BCS0028\n");
    printf("Enter the value of N (rows & columns):");
    scanf("%d", &N);
    int A[N][N];
    int T[N][N];
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = rand() %
                      100;
        }
    }
#pragma omp parallel for shared(A, T) private(i, j)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            T[j][i] = A[i][j];
        }
    }
    printf("Original Matrix (A):\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ",
                   A[i][j]);
        }
        printf("\n");
    }
    printf("Transposed Matrix (T):\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ",
                   T[i][j]);
            
        }
        printf("\n");
    }
}
#include <stdio.h>
#include <omp.h>
void main()
{
    printf("NAME: NIVED KRISHNA \n");
    printf("ROLL NUMBER: 2021BCS0028\n");
    int i, n, sum = 0;
    printf("Enter the value of n:");
    scanf("%d", &n);
    printf("With Chunk:");
#pragma omp parallel for schedule(dynamic, 2) reduction(+ : sum)
    for (i = 0; i < n + 1; i++)
    {
        sum = sum + i;
    }
    printf("%d\n", sum);
    sum = 0;
    printf("Without Chunk:");
#pragma omp parallel for schedule(dynamic) reduction(+ : sum)
    for (i = 0; i < n + 1; i++)
    {
        sum = sum + i;
    }
    printf("%d\n", sum);
}